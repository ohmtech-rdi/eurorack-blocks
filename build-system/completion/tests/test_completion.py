#!/usr/bin/env python
#
#     test_analyser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import unittest

from .. import *



class TestCompletion (unittest.TestCase):

   def test_000 (self):
      reply = complete ('erbb')
      self.assertEqual (reply, ['setup', 'init', 'configure', 'build', 'install', 'run '])

   def test_001 (self):
      reply = complete ('erbb in')
      self.assertEqual (reply, ['init', 'install'])

   def test_002 (self):
      reply = complete ('erbb init --lang')
      self.assertEqual (reply, ['--language'])

   def test_003 (self):
      reply = complete ('erbb init --language m')
      self.assertEqual (reply, ['max'])

   def test_004 (self):
      reply = complete ('erbb init --language max --name fo')
      self.assertEqual (reply, [])

   def test_005 (self):
      reply = complete ('erbb init --name foo --lan')
      self.assertEqual (reply, ['--language'])

   def test_006 (self):
      reply = complete ('erbb init --name f')
      self.assertEqual (reply, [])

if __name__ == '__main__':
   unittest.main ()
