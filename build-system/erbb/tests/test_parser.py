#!/usr/bin/env python
#
#     test_parser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

import unittest
import traceback
from .. import parser


class TestParser (unittest.TestCase):

   def test_001 (self):
      text_input = """
{
   'modules': [
      {
         'name': 'Test',
         'width': '2hp',
         'material': { 'name': 'aluminum' },
         'header': {
            'labels': [{ 'text': 'Test Header' }],
         },
         'footer': {
            'labels': [{ 'text': 'Test Footer' }],
         },

         'lines': [
            [{ 'x': '0mm', 'y': '1mm' }, { 'x': '2mm', 'y': '3mm' }],
            [{ 'x': '4.5mm', 'y': '5.6mm' }, { 'x': '1hp', 'y': '-8.0mm' }],
         ],

         'controls': [
            {
               'type': 'Pot',
               'property': 'test',
               'position': { 'x': '10.2mm', 'y': '10.3mm' },
               'style': 'rogan.6ps',
               'labels': [
                  { 'text': 'Test Center', 'positioning': 'center' },
                  { 'text': 'Test Left', 'positioning': 'left' },
                  { 'text': 'Test Top', 'positioning': 'top' },
                  { 'text': 'Test Right', 'positioning': 'right' },
                  { 'text': 'Test Bottom', 'positioning': 'bottom' },
               ],
            },
            {
               'type': 'Switch',
               'property': 'switch1',
               'position': { 'x': '1mm', 'y': '2mm' },
               'style': 'dailywell.2ms1',
               'rotation': '90°CCW',
            },
            {
               'type': 'Switch',
               'property': 'switch2',
               'position': { 'x': '3mm', 'y': '4mm' },
               'style': 'dailywell.2ms3',
               'rotation': '90°CW',
            },
            {
               'type': 'Switch',
               'property': 'switch3',
               'position': { 'x': '5mm', 'y': '1hp' },
               'style': 'dailywell.2ms1',
               'rotation': '180°CCW',
            },
         ],
      },
   ],
}
"""

      p = parser.Parser ()

      try:
         root = p.parse (text_input, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertEqual (len (root.modules), 1)
      module = root.modules [0]
      self.assertEqual (module.name, 'Test')
      self.assertEqual (module.width, 10.16)
      self.assertIsNotNone (module.material)
      self.assertTrue (module.material.is_aluminum_natural)
      self.assertFalse (module.material.is_aluminum_black)
      self.assertFalse (module.material.is_brushed_aluminum_natural)
      self.assertFalse (module.material.is_brushed_aluminum_black)
      self.assertFalse (module.material.is_aluminum_coated_white)
      self.assertFalse (module.material.is_aluminum_coated_black)

      self.assertIsNotNone (module.header)
      self.assertIsNotNone (module.header.labels)
      self.assertEqual (len (module.header.labels), 1)
      self.assertEqual (module.header.labels [0].text, 'Test Header')
      self.assertIsNone (module.header.labels [0].font)
      self.assertTrue (module.header.labels [0].positioning.is_center)
      self.assertIsNone (module.header.labels [0].position)
      self.assertEqual (module.header.labels [0].offset.x, 0)
      self.assertEqual (module.header.labels [0].offset.y, 0)

      self.assertIsNotNone (module.footer)
      self.assertIsNotNone (module.footer.labels)
      self.assertEqual (len (module.footer.labels), 1)
      self.assertEqual (module.footer.labels [0].text, 'Test Footer')
      self.assertIsNone (module.footer.labels [0].font)
      self.assertTrue (module.footer.labels [0].positioning.is_center)
      self.assertIsNone (module.footer.labels [0].position)
      self.assertEqual (module.footer.labels [0].offset.x, 0)
      self.assertEqual (module.footer.labels [0].offset.y, 0)

      self.assertIsNotNone (module.lines)
      self.assertEqual (len (module.lines), 2)
      self.assertEqual (len (module.lines [0].points), 2)
      self.assertEqual (module.lines [0].points [0].x, 0)
      self.assertEqual (module.lines [0].points [0].y, 1)
      self.assertEqual (module.lines [0].points [1].x, 2)
      self.assertEqual (module.lines [0].points [1].y, 3)
      self.assertEqual (module.lines [1].points [0].x, 4.5)
      self.assertEqual (module.lines [1].points [0].y, 5.6)
      self.assertEqual (module.lines [1].points [1].x, 5.08)
      self.assertEqual (module.lines [1].points [1].y, -8)

      self.assertIsNotNone (module.controls)
      self.assertEqual (len (module.controls), 4)

      control = module.controls [0]
      self.assertEqual (control.type, 'Pot')
      self.assertEqual (control.property, 'test')
      self.assertEqual (control.position.x, 10.2)
      self.assertEqual (control.position.y, 10.3)
      self.assertTrue (control.style.is_rogan_6ps)
      self.assertEqual (control.rotation, 0)
      self.assertIsNotNone (control.labels)
      self.assertEqual (len (control.labels), 5)
      self.assertEqual (control.labels [0].text, 'Test Center')
      self.assertTrue (control.labels [0].positioning.is_center)
      self.assertFalse (control.labels [0].positioning.is_left)
      self.assertFalse (control.labels [0].positioning.is_top)
      self.assertFalse (control.labels [0].positioning.is_right)
      self.assertFalse (control.labels [0].positioning.is_bottom)
      self.assertEqual (control.labels [1].text, 'Test Left')
      self.assertTrue (control.labels [1].positioning.is_left)
      self.assertEqual (control.labels [2].text, 'Test Top')
      self.assertTrue (control.labels [2].positioning.is_top)
      self.assertEqual (control.labels [3].text, 'Test Right')
      self.assertTrue (control.labels [3].positioning.is_right)
      self.assertEqual (control.labels [4].text, 'Test Bottom')
      self.assertTrue (control.labels [4].positioning.is_bottom)

      control = module.controls [1]
      self.assertEqual (control.type, 'Switch')
      self.assertEqual (control.property, 'switch1')
      self.assertEqual (control.position.x, 1)
      self.assertEqual (control.position.y, 2)
      self.assertTrue (control.style.is_dailywell_2ms1)
      self.assertTrue (control.style.is_dailywell_2ms)
      self.assertEqual (control.rotation, 90)
      self.assertIsNotNone (control.labels)
      self.assertEqual (len (control.labels), 0)

      control = module.controls [2]
      self.assertEqual (control.type, 'Switch')
      self.assertEqual (control.property, 'switch2')
      self.assertEqual (control.position.x, 3)
      self.assertEqual (control.position.y, 4)
      self.assertTrue (control.style.is_dailywell_2ms3)
      self.assertTrue (control.style.is_dailywell_2ms)
      self.assertEqual (control.rotation, -90)
      self.assertIsNotNone (control.labels)
      self.assertEqual (len (control.labels), 0)

      control = module.controls [3]
      self.assertEqual (control.type, 'Switch')
      self.assertEqual (control.property, 'switch3')
      self.assertEqual (control.position.x, 5)
      self.assertEqual (control.position.y, 5.08)
      self.assertTrue (control.style.is_dailywell_2ms1)
      self.assertTrue (control.style.is_dailywell_2ms)
      self.assertEqual (control.rotation, 180)
      self.assertIsNotNone (control.labels)
      self.assertEqual (len (control.labels), 0)


if __name__ == '__main__':
   unittest.main ()
