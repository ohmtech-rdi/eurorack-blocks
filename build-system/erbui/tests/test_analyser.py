#!/usr/bin/env python
#
#     test_analyser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import unittest
import traceback

from .. import ast
from ..analyser import Analyser
from . import mock



class TestAnalyser (unittest.TestCase):

   def test_normalling_000 (self):
      module = ast.Module (mock.identifier ('test_analyser_normalling_000'), None)

      analyser = Analyser ()
      analyser.make_normalling_eval_list (module)

      self.assertEqual (len (module.normalling_eval_list), 0)


   def test_normalling_001 (self):
      module = ast.Module (mock.identifier ('test_analyser_normalling_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      module.add (control)

      analyser = Analyser ()
      analyser.make_normalling_eval_list (module)

      self.assertEqual (len (module.normalling_eval_list), 1)
      self.assertEqual (module.normalling_eval_list [0].name, 'cv_in1')


   def test_normalling_002 (self):
      module = ast.Module (mock.identifier ('test_analyser_normalling_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in2'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      module.add (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.normalling_to is not None:
            analyser.resolve_normalling (module, control, control.normalling_to)

      analyser.make_normalling_eval_list (module)

      self.assertEqual (len (module.normalling_eval_list), 2)
      self.assertEqual (module.normalling_eval_list [0].name, 'cv_in2')
      self.assertEqual (module.normalling_eval_list [1].name, 'cv_in1')


   def test_normalling_002b (self):
      module = ast.Module (mock.identifier ('test_analyser_normalling_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in2'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.normalling_to is not None:
            analyser.resolve_normalling (module, control, control.normalling_to)

      analyser.make_normalling_eval_list (module)

      self.assertEqual (len (module.normalling_eval_list), 2)
      self.assertEqual (module.normalling_eval_list [0].name, 'cv_in1')
      self.assertEqual (module.normalling_eval_list [1].name, 'cv_in2')


   def test_normalling_003 (self):
      module = ast.Module (mock.identifier ('test_analyser_normalling_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in2'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in3'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in3'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in4'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in4'),
         mock.keyword ('CvIn')
      )
      module.add (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.normalling_to is not None:
            analyser.resolve_normalling (module, control, control.normalling_to)

      analyser.make_normalling_eval_list (module)

      self.assertEqual (len (module.normalling_eval_list), 4)
      self.assertEqual (module.normalling_eval_list [0].name, 'cv_in4')
      self.assertEqual (module.normalling_eval_list [1].name, 'cv_in3')
      self.assertEqual (module.normalling_eval_list [2].name, 'cv_in2')
      self.assertEqual (module.normalling_eval_list [3].name, 'cv_in1')


   def test_normalling_003b (self):
      module = ast.Module (mock.identifier ('test_analyser_normalling_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in4'),
         mock.keyword ('CvIn')
      )
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in3'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in4'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in3'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in2'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.normalling_to is not None:
            analyser.resolve_normalling (module, control, control.normalling_to)

      analyser.make_normalling_eval_list (module)

      self.assertEqual (len (module.normalling_eval_list), 4)
      self.assertEqual (module.normalling_eval_list [0].name, 'cv_in1')
      self.assertEqual (module.normalling_eval_list [1].name, 'cv_in2')
      self.assertEqual (module.normalling_eval_list [2].name, 'cv_in3')
      self.assertEqual (module.normalling_eval_list [3].name, 'cv_in4')


   def test_normalling_003c (self):
      module = ast.Module (mock.identifier ('test_analyser_normalling_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in3'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in4'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in3'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in4'),
         mock.keyword ('CvIn')
      )
      module.add (control)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      normalling_from = ast.NormallingFrom (mock.identifier ('cv_in2'), ast.Control)
      control.add (normalling_from)
      module.add (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.normalling_to is not None:
            analyser.resolve_normalling (module, control, control.normalling_to)

      analyser.make_normalling_eval_list (module)

      self.assertEqual (len (module.normalling_eval_list), 4)
      self.assertEqual (module.normalling_eval_list [0].name, 'cv_in1')
      self.assertEqual (module.normalling_eval_list [1].name, 'cv_in4')
      self.assertEqual (module.normalling_eval_list [2].name, 'cv_in2')
      self.assertEqual (module.normalling_eval_list [3].name, 'cv_in3')


if __name__ == '__main__':
   unittest.main ()
