#!/usr/bin/env python3
#
#     monitor.py
#     Copyright (c) 2026 Raphael DINGE
#
#     Host side of the erb monitor (erb_MONITOR=1): manages an openocd RTT
#     server over the debug probe and speaks the fourcc-box protocol with
#     the firmware (see include/erb/RttProtocol.h).
#
#     Built-in commands: ping, load, prof, stream (raw text tail).
#     Applications layer their own commands on top of Session.
#
#Tab=3---------------------------------------------------------------------

import os
import re
import socket
import struct
import subprocess
import time

RTT_PORT = 19021

# the control block lives in the non-cacheable DMA RAM region (see erb/Rtt.h)
RTT_SEARCH_ADDRESS = '0x30000000'
RTT_SEARCH_SIZE = '0x8000'



#-- server --------------------------------------------------------------------

def start_server (adapter_speed_khz=None, log_path=None):
   cmd = [
      'openocd',
      '-f', 'interface/stlink.cfg',
      '-f', 'target/stm32h7x.cfg',
   ]
   if adapter_speed_khz is not None:
      cmd += ['-c', 'adapter speed %d' % adapter_speed_khz]
   cmd += [
      '-c', 'init',
      '-c', 'rtt setup %s %s "SEGGER RTT"' % (RTT_SEARCH_ADDRESS, RTT_SEARCH_SIZE),
      '-c', 'rtt polling_interval 1',
      '-c', 'rtt start',
      '-c', 'rtt server start %d 0' % RTT_PORT,
   ]
   log_file = open (log_path, 'w') if log_path else subprocess.DEVNULL
   return subprocess.Popen (cmd, stdout=log_file, stderr=subprocess.STDOUT)


def stop_server (process):
   process.terminate ()
   try:
      process.wait (timeout=5)
   except subprocess.TimeoutExpired:
      process.kill ()



#-- session -------------------------------------------------------------------

class Session:
   def __init__ (self, port=RTT_PORT, connect_timeout_s=10.0):
      self._sock = None
      deadline = time.time () + connect_timeout_s
      while time.time () < deadline and self._sock is None:
         try:
            self._sock = socket.create_connection (('127.0.0.1', port), timeout=1.0)
         except OSError:
            time.sleep (0.2)
      if self._sock is None:
         raise TimeoutError ('cannot connect to the RTT server')
      self._sock.settimeout (0.05)
      self._buf = b''

   def close (self):
      self._sock.close ()

   # openocd forwards TCP input to the down ring at its polling pace; pushing
   # a big payload in one write can stall its forwarding. Pace it in chunks.
   CHUNK = 2048
   CHUNK_DELAY_S = 0.002

   def send_box (self, cmd, payload=b''):
      assert len (cmd) == 4
      data = struct.pack ('<I', len (payload)) + cmd.encode ('ascii') + payload
      pos = 0
      while pos < len (data):
         # sendall state is undefined on timeout: use send with explicit
         # offsets, and treat timeouts as TCP backpressure (openocd's pace)
         try:
            pos += self._sock.send (data [pos:pos + self.CHUNK])
         except socket.timeout:
            continue
         if len (data) > self.CHUNK:
            time.sleep (self.CHUNK_DELAY_S)

   def read_line (self, timeout_s=1.0):
      deadline = time.time () + timeout_s
      while time.time () < deadline:
         if b'\n' in self._buf:
            raw, self._buf = self._buf.split (b'\n', 1)
            return raw.decode ('utf-8', errors='replace').rstrip ('\r')
         try:
            chunk = self._sock.recv (4096)
         except socket.timeout:
            continue
         except OSError:
            break
         if chunk:
            self._buf += chunk
      return None

   # A leftover mid-box parser state (aborted previous session) eats the
   # first command; the firmware self-heals after its 2 s stall timeout.
   # hello () absorbs that: ping, and on silence ping again once the drop
   # has fired.
   def hello (self):
      for attempt in range (2):
         self.send_box ('ping')
         try:
            self.expect (r'^ok ping$', timeout_s=3.5)
            return
         except TimeoutError:
            if attempt == 0:
               time.sleep (2.5)
      raise TimeoutError ('no ping reply - board unreachable?')

   def expect (self, pattern, timeout_s=5.0):
      deadline = time.time () + timeout_s
      while time.time () < deadline:
         line = self.read_line (timeout_s=deadline - time.time ())
         if line is None:
            break
         m = re.search (pattern, line)
         if m:
            return line, m
      raise TimeoutError ('expect (%r) timed out' % pattern)



#-- built-in commands ---------------------------------------------------------

def run_ping (session):
   t0 = time.time ()
   session.send_box ('ping')
   session.expect (r'^ok ping$')
   print ('ok ping (%.0f ms)' % ((time.time () - t0) * 1000.0))


# Measure the audio callback load over a bounded window. Returns
# (busy_max, busy_avg, period_avg) in CPU cycles, all measured
# firmware-side (self-calibrated budget). The firmware accumulators are
# 32-bit: the first query only resets them, the second collects — an
# unbounded window would overflow (~20 s at high load).

def run_load (session, quiet=False, window_s=1.0):
   session.send_box ('load')
   session.expect (r'^(ok|err) load')
   time.sleep (window_s)

   session.send_box ('load')
   line, m = session.expect (
      r'^ok load blocks=(\d+) busy_max=(\d+) busy_avg=(\d+) period_avg=(\d+)$'
   )
   blocks = int (m.group (1))
   busy_max = int (m.group (2))
   busy_avg = int (m.group (3))
   period_avg = int (m.group (4))

   if not quiet:
      print ('%s' % line)
      if period_avg > 0:
         print ('load: avg %5.1f %%  max %5.1f %%  (%d blocks)' % (
            100.0 * busy_avg / period_avg,
            100.0 * busy_max / period_avg,
            blocks
         ))

   return busy_max, busy_avg, period_avg


# Start a profiler window, collect the dump, render the node tree and the
# by-label aggregate table. Labels are application-defined fourccs;
# percentages use the audio callback period measured by `load`.

def run_prof (session, nbr_blocks):
   _, _, period_avg = run_load (session, quiet=True)

   session.send_box ('prof', struct.pack ('<I', nbr_blocks))
   line, _ = session.expect (r'^(ok|err) prof')
   print (line)
   if not line.startswith ('ok'):
      return

   nodes = {}
   probes = {}
   while True:
      line = session.read_line (timeout_s=nbr_blocks / 3000.0 + 10.0)
      if line is None:
         print ('prof: dump timed out')
         break
      m = re.match (r'^prof (\d+) (....) (-?\d+) (\d+)$', line)
      if m:
         nodes [int (m.group (1))] = {
            'label': m.group (2),
            'parent': int (m.group (3)),
            'cycles': int (m.group (4)),
         }
         continue
      m = re.match (r'^probp (\d+) (\d+) (\d+)$', line)
      if m:
         probes [int (m.group (1))] = (int (m.group (2)), int (m.group (3)))
         continue
      if line.startswith ('ok prof'):
         print (line)
         break

   m = re.search (r'blocks=(\d+)', line or '')
   blocks = max (int (m.group (1)) if m else nbr_blocks, 1)

   children = {}
   roots = []
   for index, node in nodes.items ():
      if node ['parent'] < 0:
         roots.append (index)
      else:
         children.setdefault (node ['parent'], []).append (index)

   def exclusive (index):
      return nodes [index]['cycles'] - sum (
         nodes [c]['cycles'] for c in children.get (index, [])
      )

   print ('%-32s %10s %10s %8s' % ('node', 'incl/blk', 'excl/blk', '%period'))

   def render (index, depth):
      node = nodes [index]
      incl = node ['cycles'] / blocks
      excl = exclusive (index) / blocks
      pct = 100.0 * incl / period_avg if period_avg > 0 else 0.0
      print ('%-32s %10.0f %10.0f %7.2f%%' % (
         '%s%-3d %s' % ('  ' * depth, index, node ['label']), incl, excl, pct
      ))
      for c in children.get (index, []):
         render (c, depth + 1)

   for index in sorted (roots):
      render (index, 0)

   # aggregate by label, exclusive cycles (inclusive would double-count
   # parents and children): the ranking view
   totals = {}
   for index, node in nodes.items ():
      entry = totals.setdefault (node ['label'], [0, 0])
      entry [0] += 1
      entry [1] += exclusive (index)

   print ()
   print ('%-6s %5s %10s %8s' % ('label', 'count', 'excl/blk', '%period'))
   for label, (count, cycles) in sorted (totals.items (), key=lambda kv: -kv [1][1]):
      pct = 100.0 * (cycles / blocks) / period_avg if period_avg > 0 else 0.0
      print ('%-6s %5d %10.0f %7.2f%%' % (label, count, cycles / blocks, pct))

   for index, (cycles, count) in sorted (probes.items ()):
      print ('probe %-2d  %8.0f cyc/blk  %8.1f cyc/call  x%.1f calls/blk' % (
         index, cycles / blocks,
         cycles / max (count, 1), count / blocks
      ))


# Tail the up channel as text lines (firmware printf traffic), optionally
# teeing the stamped lines to a log file.

def run_stream (session, duration_s=None, log_path=None):
   log_file = open (log_path, 'w', buffering=1) if log_path else None
   nbr_lines = 0
   t0 = time.time ()
   try:
      while (duration_s is None) or (time.time () - t0 < duration_s):
         line = session.read_line (timeout_s=0.5)
         if line is not None:
            stamped = '[%8.3f] %s' % (time.time () - t0, line)
            print (stamped)
            if log_file is not None:
               log_file.write (stamped + '\n')
            nbr_lines += 1
   except KeyboardInterrupt:
      pass
   finally:
      if log_file is not None:
         log_file.close ()
         print ('log: %s' % log_path)
      if nbr_lines == 0:
         print ('warning: no output — app running?')
