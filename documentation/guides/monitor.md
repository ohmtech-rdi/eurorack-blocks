# Measuring a Running Module

When optimising a module, the numbers that matter are the ones measured on
the real hardware, while the module runs: the audio callback load, and where
the cycles go. **monitor** provides that over a ST-Link debug probe.

It is built on [RTT](https://github.com/SEGGERMicro/RTT):
a small control block in RAM that the debug probe reads
and writes over SWD while the CPU runs, with no halt and no trap.
On top of it, a tiny command protocol lets the host query the module
and lets your module expose its own custom commands.


## Enabling the monitor

Add the define to your `erbb` module definition:

```erbb
module MyModule {
   define erb_MONITOR=1
   ...
}
```

Then rebuild and flash:

```shell-session
$ erbb configure
$ erbb build
$ erbb install
```


## Talking to the module

`erbb monitor` manages the debug link (it starts OpenOCD internally) and
speaks to the running module:

```shell-session
$ erbb monitor ping
ok ping (11 ms)
```

`load` reports the audio callback CPU load.

```shell-session
$ erbb monitor load
ok load blocks=143210 busy_max=98123 busy_avg=91456 period_avg=159953
load: avg  57.2 %  max  61.3 %  (143210 blocks)
```

Note that for your module, the "max" value is the only important for hard
realtime. "avg" is just giving a hint of audio spikes if any.
Audio drops start when max is around 90% of the MCU.

`stream` outputs everything the firmware prints with `erb::Monitor::use ().printf`.
`--duration` can be used to run only for a specified amount of time,
and is typically used with automated tools.

```shell-session
$ erbb monitor stream --duration 10
```

When the module is hard to reach or the link is slow, `--speed-khz` sets
the debug probe adapter speed.


## Bench setup

When iterating on the module code, the edit / build / flash / measure loop
can run unattended from a single command:

```shell-session
$ erbb monitor --build --install --duration 10
```

`--build` configures and builds the firmware first, `--install` flashes it,
and the monitor then runs the requested action (`stream` when not
specified). `--log <file>` outputs the streamed lines, with timestamps, to a
file, and warns when nothing was received at all.

This needs the board connected with **both** cables:

- the USB cable, powering the board and using DFU transfer,
- the ST-Link probe, using the monitor link to reset and open
  the DFU window.

With the probe connected, `erbb install` (and `erbb monitor --install`)
enters the Daisy bootloader by resetting the board through the probe and
catching the DFU window that the bootloader opens on boot, no button press
needed. The stock bootloader variant installed by `erbb install bootloader`
(`intdfu-2000ms`) opens that window for 2 seconds on every reset.

After a dependency or branch change, `--rebuild` wipes `artifacts/daisy`
before building:

```shell-session
$ erbb monitor --rebuild --install --duration 10
```


## Profiling

The profiler measures where the cycles go, over a window of audio blocks.
An audio block is one audio callback invocation, processing
`erb_BUFFER_SIZE` frames, `/blk` in the outputs below reads *per block*.

Your module describes its structure once as a tree of nodes. A node is
anything you want to time: a processing section, a voice, etc.

`erb_PROFILER_REGISTER` registers a node and stores its index in the
variable passed as second argument. Indices start at 0 and are incremented
with each registration.

A tree structure can be represented by passing the parent node index
to the child, as third argument.
For example here, a voice node with its oscillator and envelope as children,
and a reverb next to it.

```c++
#include "erb/erb.h"

struct MyModule
{
   // ...

   std::size_t _voice_node;
   std::size_t _osc_node;
   std::size_t _env_node;
   std::size_t _reverb_node;

   void init ()
   {
      erb_PROFILER_REGISTER ("voic", _voice_node);
         erb_PROFILER_REGISTER ("osc ", _osc_node, _voice_node);
         erb_PROFILER_REGISTER ("env ", _env_node, _voice_node);
      erb_PROFILER_REGISTER ("revb", _reverb_node);
   }
};
```

Like the other profiler macros, it compiles to nothing when the monitor is
absent.

Labels are **exactly 4 characters** (pad with spaces when needed eg. `"env "`).

Labels are display tags for the host tree and they can be reused.
A polyphonic module can register one node per voice, all labeled
`"voic"`. Each node keeps its own cycle count: the host shows them as
separate lines in the tree, and sums equal labels in the aggregate table
that follows it.

Then instrument the code paths with `erb_PROFILER_SCOPE`: it measures the
enclosing scope and adds the cycles to the node. The macro compiles to
nothing when the monitor is absent.

```c++
void process ()
{
   {
      erb_PROFILER_SCOPE (_voice_node);

      process_voice ();   // internally times _osc_node and _env_node the same way
   }

   {
      erb_PROFILER_SCOPE (_reverb_node);

      process_reverb ();
   }
}
```

Run a profiling window:

```shell-session
$ erbb monitor prof
ok prof started blocks=3000
ok prof blocks=3000 nodes=4 truncated=0
node                               incl/blk   excl/blk  %period
0   voic                              41220      12451   25.77%
  1   osc                             19875      19875   12.42%
  2   env                              8894       8894    5.56%
3   revb                              30112      30112   18.82%

label  count   excl/blk  %period
revb       1      30112   18.82%
osc        1      19875   12.42%
voic       1      12451    7.78%
env        1       8894    5.56%
```

Children indent under their parent; `incl` is the node's own measured
cycles, `excl` subtracts the children. Here the voice spends 12,451
cycles per block (`/blk`) outside its oscillator and envelope.

The aggregate table below the tree sums the exclusive cycles of equal
labels, sorted by cost: with many nodes it is the view to read first.

### Probes

For quick ad-hoc section timing without registering nodes,
`erb_PROFILER_SCOPE_PROBE` accumulates cycles and call counts into flat
slots:

```c++
   {
      erb_PROFILER_SCOPE_PROBE (0);

      spectral_convolve ();
   }
```

Probes are reported after the node tree, with per-call statistics:

```shell-session
probe 0       3211 cyc/blk     200.7 cyc/call  x16.0 calls/blk
```

## Module-specific commands

The protocol carries fourcc-labeled boxes: `[u32 payload_size][fourcc]
[payload]`. Your module can register its own commands next to the built-in
ones (`ping`, `sink`, `load`, `prof`), for example to inject a stimulus (a gate trigger, or knob move), or stream data in (acting like a SD card):

Handlers are plain function pointers: a lambda works as long as it
captures nothing, module state travels through the context pointer
instead:

```c++
void MyModule::init ()
{
   // ...
#if (erb_MONITOR)
   erb::Monitor::use ().register_command (
      erb::RttProtocol::fourcc ("gain"), this,
      [] (void * ctx, std::span <const std::uint8_t> payload)
      {
         auto & module = *static_cast <MyModule *> (ctx);

         if (payload.size () != sizeof (float))
         {
            erb::Monitor::use ().printf ("err gain payload\n");
            return;
         }

         std::memcpy (&module._gain, payload.data (), sizeof (float));
         erb::Monitor::use ().printf ("ok gain\n");
      }
   );
#endif
}
```

## Streaming data in

Command payloads are bounded (128 bytes). For unbounded transfers, eg.
uploading a wavetable, a sample, a preset bank, register a *stream*
handler: it is called when the box header arrives and pulls the payload
itself, at its own pace, while the transport handles flow control. Here the
host sends `[wavetable floats][crc32]` and the module checks integrity end
to end:

```c++
void MyModule::init ()
{
   // ...
#if (erb_MONITOR)
   erb::Monitor::use ().register_stream (
      erb::RttProtocol::fourcc ("wavt"), this,
      [] (void * ctx, std::size_t payload_size)
      {
         auto & module = *static_cast <MyModule *> (ctx);

         const std::size_t data_size = payload_size - 4;

         if (data_size > sizeof (module._wavetable))
         {
            erb::Monitor::use ().printf ("err wavt too big\n");
            return;  // the protocol drains and discards the rest
         }

         erb::RttProtocol::use ().stream_crc_reset ();

         if (erb::RttProtocol::use ().stream_read (&module._wavetable, data_size) != data_size)
         {
            erb::Monitor::use ().printf ("err wavt timeout\n");
            return;
         }

         std::uint32_t crc_expected = 0;
         erb::RttProtocol::use ().stream_read_raw (&crc_expected, 4);

         if (erb::RttProtocol::use ().stream_crc () != crc_expected)
         {
            erb::Monitor::use ().printf ("err wavt crc\n");
            return;
         }

         erb::Monitor::use ().printf ("ok wavt bytes=%lu\n",
            static_cast <unsigned long> (data_size));
      }
   );
#endif
}
```

Note that the handler runs while the host is still sending: `stream_read`
blocks until the requested bytes have arrived, so the payload flows
*through* the module rather than being accumulated somewhere first, so it can
be far larger than any buffer on the module. The transfer above writes each
chunk into `_wavetable` as it lands, at link speed. Reading everything in
one call is a convenience: a handler can equally loop over a small scratch
buffer and process the data piecewise.

On the host side, `build-system/erbb/monitor.py` exposes the session object
for your own scripts, here the sender for the transfer above (the standard
`zlib.crc32` matches the module-side CRC-32):

```python
import struct
import sys
import zlib

sys.path.append ('/path/to/eurorack-blocks/build-system')

from erbb import monitor

process = monitor.start_server ()
try:
   session = monitor.Session ()
   session.hello ()

   data = open ('wavetable.f32', 'rb').read ()
   session.send_box ('wavt', data + struct.pack ('<I', zlib.crc32 (data)))
   session.expect (r'^ok wavt', timeout_s=60.0)

finally:
   monitor.stop_server (process)
```


## Advanced

### Debug Probe

This feature is for the daisy target only,
and a debug probe must be connected.
`erbb monitor` and `erbb install` share the probe so that monitoring stops while flashing.

### Transport Limits

The openocd RTT server drops down-channel bytes whenever a TCP burst finds
its 4 KB ring full, a random event under host scheduler jitter,
correlated with long transfers.
Byte *counts* stay intact (later bytes shift in),
so the protocol parser desynchronizes silently and fails at the
first shifted pseudo-header:
the failure point is content-deterministic
(typically the first large box) while the failure occurrence is random,
which can look like a logic bug.

Workarounds:

- `erb_MONITOR_FIFO_SIZE` enlarges the module-side stream fifo, covering
  the parser-stall class of ring-full events.
- An end-to-end crc plus host-side retry (as in the streaming example
  above) converts residual drops from wrong results into a retried
  transfer.

Unfortunately a proper fix would be to add flow control in the openocd
RTT server itself, or a host pacing handshake.

### SEGGER Licensing

the RTT control block follows the SEGGER RTT memory layout
so that standard probe software can find it. This is an independent
implementation (no SEGGER source code, see `src/Rtt.cpp`), permitted for
debugging and logging purposes. The monitor is a development tool: **do
not distribute firmware built with `erb_MONITOR` enabled**. ship with
the define absent or set to 0, which removes every trace of it from the
binary.

### Memory Cost

The profiler tables cost about 12 KB of static storage (`.bss`), which
lives in the internal RAM region your linker script maps it to, AXI SRAM
on the stock Daisy layout, RAM_D2 with the erb `sram` section. Budget for
it if your module is close to that region's limit.

Node storage is static and bounded: 1024 nodes
(`erb::Profiler::MaxNbrNodes`). Past the limit, `register_node` returns an
out-of-range handle that `add` safely ignores, and the condition is
reported both programmatically (`erb::Profiler::use ().truncated ()`) and in the
`prof` output (`truncated=1`), so an overflow can never silently produce a
partial tree that looks complete.

### Dynamic Node Registration

Registration happens at runtime, so the tree can follow structures that
only exist at runtime: a module that rebuilds its processing graph per
preset re-registers on each rebuild, `erb::Profiler::use ().reset_nodes ()`
clears the table first, and stores each handle alongside the processing
step it times, instead of in named members.
A module whose structure is fixed registers once in `init` and never calls `reset_nodes`.

### Profiling Window Length

`--blocks` sets the window length, 3000 audio blocks when not specified,
about 3 seconds at typical block rates.

The window is an average: make it span the scenario being measured (a full
musical phrase, the worst-case preset with its transients), not just the
instant the command is typed. Longer windows smooth the average but have a
ceiling: each node accumulates cycles in a 32-bit counter, so a node close
to the full budget wraps past roughly 25,000 blocks, so stay well below.

The length is expressed in audio blocks rather than seconds because blocks
are what the firmware natively counts, and the monitor is deliberately
configuration-free: neither side knows the CPU clock or block rate, so a
seconds conversion would only be a guess.

### Scope Probes Internals

The underlying API stays public for cases the scope form does not fit:
`erb::CycleCounter::now` and, on `erb::Profiler::use ()`, `add` and
`register_node` (which the macros wrap).

