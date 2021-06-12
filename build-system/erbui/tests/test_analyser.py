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

   def test_cascade_000 (self):
      module = ast.Module (mock.identifier ('test_analyser_cascade_000'), None)

      analyser = Analyser ()
      analyser.make_cascade_eval_list (module)

      self.assertEqual (len (module.cascade_eval_list), 0)


   def test_cascade_001 (self):
      module = ast.Module (mock.identifier ('test_analyser_cascade_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      module.entities.append (control)

      analyser = Analyser ()
      analyser.make_cascade_eval_list (module)

      self.assertEqual (len (module.cascade_eval_list), 1)
      self.assertEqual (module.cascade_eval_list [0].name, 'cv_in1')


   def test_cascade_002 (self):
      module = ast.Module (mock.identifier ('test_analyser_cascade_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in2'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      module.entities.append (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.cascade_to is not None:
            analyser.resolve_cascade (module, control, control.cascade_to)

      analyser.make_cascade_eval_list (module)

      self.assertEqual (len (module.cascade_eval_list), 2)
      self.assertEqual (module.cascade_eval_list [0].name, 'cv_in1')
      self.assertEqual (module.cascade_eval_list [1].name, 'cv_in2')


   def test_cascade_002b (self):
      module = ast.Module (mock.identifier ('test_analyser_cascade_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in2'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.cascade_to is not None:
            analyser.resolve_cascade (module, control, control.cascade_to)

      analyser.make_cascade_eval_list (module)

      self.assertEqual (len (module.cascade_eval_list), 2)
      self.assertEqual (module.cascade_eval_list [0].name, 'cv_in1')
      self.assertEqual (module.cascade_eval_list [1].name, 'cv_in2')


   def test_cascade_003 (self):
      module = ast.Module (mock.identifier ('test_analyser_cascade_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in2'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in3'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in3'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in4'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in4'),
         mock.keyword ('CvIn')
      )
      module.entities.append (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.cascade_to is not None:
            analyser.resolve_cascade (module, control, control.cascade_to)

      analyser.make_cascade_eval_list (module)

      self.assertEqual (len (module.cascade_eval_list), 4)
      self.assertEqual (module.cascade_eval_list [0].name, 'cv_in1')
      self.assertEqual (module.cascade_eval_list [1].name, 'cv_in2')
      self.assertEqual (module.cascade_eval_list [2].name, 'cv_in3')
      self.assertEqual (module.cascade_eval_list [3].name, 'cv_in4')


   def test_cascade_003b (self):
      module = ast.Module (mock.identifier ('test_analyser_cascade_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in4'),
         mock.keyword ('CvIn')
      )
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in3'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in4'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in3'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in2'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.cascade_to is not None:
            analyser.resolve_cascade (module, control, control.cascade_to)

      analyser.make_cascade_eval_list (module)

      self.assertEqual (len (module.cascade_eval_list), 4)
      self.assertEqual (module.cascade_eval_list [0].name, 'cv_in1')
      self.assertEqual (module.cascade_eval_list [1].name, 'cv_in2')
      self.assertEqual (module.cascade_eval_list [2].name, 'cv_in3')
      self.assertEqual (module.cascade_eval_list [3].name, 'cv_in4')


   def test_cascade_003c (self):
      module = ast.Module (mock.identifier ('test_analyser_cascade_001'), None)

      control = ast.Control (
         mock.identifier ('cv_in3'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in4'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in2'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in3'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in4'),
         mock.keyword ('CvIn')
      )
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('cv_in1'),
         mock.keyword ('CvIn')
      )
      cascade_to = ast.CascadeTo (mock.identifier ('cv_in2'))
      control.entities.append (cascade_to)
      module.entities.append (control)

      analyser = Analyser ()
      for control in module.controls:
         if control.cascade_to is not None:
            analyser.resolve_cascade (module, control, control.cascade_to)

      analyser.make_cascade_eval_list (module)

      self.assertEqual (len (module.cascade_eval_list), 4)
      self.assertEqual (module.cascade_eval_list [0].name, 'cv_in1')
      self.assertEqual (module.cascade_eval_list [1].name, 'cv_in2')
      self.assertEqual (module.cascade_eval_list [2].name, 'cv_in3')
      self.assertEqual (module.cascade_eval_list [3].name, 'cv_in4')


if __name__ == '__main__':
   unittest.main ()
