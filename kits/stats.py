#!/usr/bin/env python
#
#     stats.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from collections import Counter
import csv
import logging
import os
import sys
import subprocess



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



"""
==============================================================================
Name : make_target
==============================================================================
"""

def make_target ():
   conf = open (os.path.join (PATH_THIS, 'panel-daisy-conf.py'), "r").read ()
   dict = eval (conf)
   dict ['audio-in'] = dict.pop ('audio-in-daisy')
   dict ['audio-out'] = dict.pop ('audio-out-daisy')
   dict.pop ('multiplexer')
   dict.pop ('power-bus')
   dict.pop ('regulator-daisy')
   return dict



"""
==============================================================================
Name : compute_coverage
==============================================================================
"""

def compute_coverage (distribution, target):
   for feature, target_nbr in target.iteritems ():
      dist_feature = distribution [feature]
      partial_arr = [dist_feature [i] for i in dist_feature if i <= target_nbr]
      partial = float (sum (partial_arr))
      total_arr = [dist_feature [i] for i in dist_feature]
      total = float (sum (total_arr))
      if total == 0.0:
         percent = 100.0
      else:
         percent = 100.0 * partial / total
      print '%s: %f%%' % (feature, percent)



"""
==============================================================================
Name : stats
==============================================================================
"""

def stats ():
   file = open (os.path.join (PATH_THIS, 'modular-grid-popular-digital.csv'))
   rows = csv.reader (file, delimiter=';')

   first_line = True
   headers = []
   distribution = dict ()

   for row in rows:
      row_values = row [1:]
      if first_line:
         # First line is features headers
         for header in row_values:
            headers.append (header)
         for i, header_name in enumerate (row_values):
            header = headers [i]
            distribution [header] = Counter ()
         first_line = False
      else:
         for i, value in enumerate (row_values):
            header = headers [i]
            feature_dist = distribution [header]
            feature_dist [int (value)] += 1

   for i in xrange (1, 4):
      target = make_target ()
      for elem in target:
         target [elem] *= i

      print 'Panel x%s' % i
      compute_coverage (distribution, target)
      print ''





##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (stats ())

   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Stats command exited with %d' % error.returncode
      sys.exit(1)
