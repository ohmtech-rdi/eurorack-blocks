import bpy

import os
import random

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ARTIFACTS = os.path.join (PATH_THIS, 'artifacts')

UNIT = 1.0
CLEARANCE = 0.125
TOLERANCE = 0.1
WALL = 1
BASE_HEIGHT = 8.5

x_min = None
x_max = None
y_min = None
y_max = None

holes = []
keys = []
positions = {}



#-----------------------------------------------------------------------------

def clear_scene ():
   # clear default cube
   bpy.ops.object.select_all (action='SELECT')
   bpy.ops.object.delete (use_global=False)


#-----------------------------------------------------------------------------

def to_location (x, y, z):
   return (x * UNIT, - y * UNIT, z * UNIT)


#-----------------------------------------------------------------------------

def to_scale (width, height, depth):
   return (width * UNIT, height * UNIT, depth * UNIT)


#-----------------------------------------------------------------------------

def to_rotation (r):
   return (0, 0, r)


#-----------------------------------------------------------------------------

def opt_eval (lhs, rhs, fn):
   if lhs is None:
      return rhs
   else:
      return fn (lhs, rhs)


#-----------------------------------------------------------------------------

def add_box (name, x, y, width, height, z_min, z_max, tolerance):
   epsilon = 0.001
   center_x = x + width * 0.5
   center_y = y + height * 0.5
   center_z = (z_min + z_max) * 0.5
   bpy.ops.mesh.primitive_cube_add (
      size=2, enter_editmode=False, align='WORLD',
      location=to_location (center_x, center_y, center_z),
      scale=to_scale (
         width + tolerance * 2 + random.uniform (-epsilon, epsilon),
         height + tolerance * 2 + random.uniform (-epsilon, epsilon),
         z_max - z_min + tolerance * 2 + random.uniform (-epsilon, epsilon),
      )
   )

   left = center_x - width * 0.5 - tolerance
   right = center_x + width * 0.5 + tolerance
   top = center_y - height * 0.5 - tolerance
   bottom = center_y + height * 0.5 + tolerance

   global positions
   positions [name] = {
      'left': left,
      'right': right,
      'top': top,
      'bottom': bottom,
   }

   bpy.context.active_object.name = name


#-----------------------------------------------------------------------------

def add_pin_header (name, x, y, rotation, nbr_position, nbr_row):

   if nbr_row == 1:
      width = 2.38
   elif nbr_row == 2:
      width = 5

   if rotation == 0:
      left = x - 2.38 * 0.5
      top = y - (1.27 + 0.25)
      right = left + width
      bottom = y + 2.54 * (nbr_position - 1) + 1.27 + 0.25
   elif rotation == 90:
      left = x - (1.27 + 0.25)
      top = y - 2.38 * 0.5
      right = x + 2.54 * (nbr_position - 1) + 1.27 + 0.25
      bottom = top + width
   else:
      print ('Unsupported rotation')

   global x_min
   global x_max
   global y_min
   global y_max
   x_min = opt_eval (x_min, left, min)
   x_max = opt_eval (x_max, right, max)
   y_min = opt_eval (y_min, top, min)
   y_max = opt_eval (y_max, bottom, max)

   add_box (name, left, top, right - left, bottom - top, -8, 8, CLEARANCE)

   global holes
   holes.append (name)


#-----------------------------------------------------------------------------

def add_pin_header_holes (name, x, y, nbr_position, nbr_row):

   for pos in range (nbr_position):
      for row in range (nbr_row):
         add_pin_hole ('%s-%d-%d' % (name, pos, row), x + pos * 2.54, y + row * 2.54)


#-----------------------------------------------------------------------------

def add_pin_hole (name, x, y):
   global holes

   width = 0.64
   left = x - width * 0.5
   right = x + width * 0.5
   top = y - width * 0.5
   bottom = y + width * 0.5
   box_name = '%s-hole' % name
   add_box (box_name, left, top, right - left, bottom - top, -8, 8, CLEARANCE)
   holes.append (box_name)


#-----------------------------------------------------------------------------

def add_shrouded_header (name, x, y):
   # x, y is pin1, which is the top right
   center_x = x - 1.27
   center_y = y + 2.54 * 2
   left = center_x - 8.85 * 0.5 - (9.1 - 8.85)
   right = center_x + 8.85 * 0.5
   top = center_y - 20.36 * 0.5
   bottom = center_y + 20.36 * 0.5

   hole_name = '%s-hole' % name
   add_box (hole_name, left, top, right - left, bottom - top, -8, 8, CLEARANCE)

   global holes
   holes.append (hole_name)

   left2 = right - 1.5
   right2 = right + 1.5
   top = center_y - 4.5 * 0.5
   bottom = center_y + 4.5 * 0.5
   z_max = BASE_HEIGHT * 0.5 - (9.1 - 6.5) + CLEARANCE
   z_min = - BASE_HEIGHT * 0.5

   key_name = '%s-key' % name
   add_box (
      key_name,
      left2, top,
      right2 - left2, bottom - top,
      z_min, z_max,
      -CLEARANCE
   )

   global keys
   keys.append (key_name)


#-----------------------------------------------------------------------------

def add_cavity (base, left, top, right, bottom):
   z = - BASE_HEIGHT * 0.5 + 2.54 + TOLERANCE

   name = ''.join (random.choice ('0123456789abcdef') for n in range (30))
   add_box (name, left, top, right - left, bottom - top, z + 1, 8, 0)
   add_modifier_boolean (base, name, 'DIFFERENCE')

   name = ''.join (random.choice ('0123456789abcdef') for n in range (30))
   add_box (name, left, top, right - left, bottom - top, -8, z, 0)
   add_modifier_boolean (base, name, 'DIFFERENCE')


#-----------------------------------------------------------------------------

def add_modifier_boolean (base, other, operation):
   objects = bpy.data.objects
   base_obj = objects [base]
   other_obj = objects [other]

   modifier = base_obj.modifiers.new (type="BOOLEAN", name=other)
   modifier.object = other_obj
   modifier.operation = operation
   other_obj.hide_set (True)


#-----------------------------------------------------------------------------

clear_scene ()

if not os.path.exists (PATH_ARTIFACTS):
   os.makedirs (PATH_ARTIFACTS)

add_pin_header ('J3', 1.77, 18.39, 0, 8, 1)
add_pin_header ('J6', 1.77, 41.25, 0, 4, 1)
add_pin_header ('J7', 1.77, 56.49, 0, 8, 1)
add_pin_header ('J5', 1.77, 94.59, 0, 10, 1)

add_pin_header ('J4', 4.31, 10.77, 90, 8, 1)
add_pin_header ('J11', 29.71, 10.77, 90, 2, 1)
add_pin_header ('J12', 38.6, 10.77, 90, 8, 1)

add_pin_header ('J1', 58.92, 18.39, 0, 12, 1)
add_pin_header ('J9', 58.92, 51.41, 0, 2, 1)
add_pin_header ('J10', 58.92, 59.03, 0, 6, 1)
add_pin_header ('J2', 58.92, 97.13, 0, 9, 1)

add_pin_header ('DPSM1', (20.663 + 20.917) * 0.5, 47.27, 0, 5, 2)
add_pin_header ('DPSM2', (48.663 + 48.917) * 0.5, 47.27, 0, 5, 2)
add_pin_header ('DPSM3', 17.98, (105.953 + 106.207) * 0.5, 90, 5, 2)
add_pin_header ('DPSM4', 43.98, (105.953 + 106.207) * 0.5, 90, 5, 2)


add_pin_header_holes ('SD', 46.855, 61.57, 3, 6)
add_pin_header_holes ('CI', 47.49, 97.13, 3, 2)

add_box (
   'Base',
   x_min - WALL, y_min - WALL,
   x_max - x_min + WALL * 2, y_max - y_min + WALL * 2,
   -BASE_HEIGHT * 0.5, BASE_HEIGHT * 0.5,
   0
)

print ('Base width: %f' % (x_max - x_min + WALL * 2))
print ('Base height: %f' % (y_max - y_min + WALL * 2))

for hole in holes:
   add_modifier_boolean ('Base', hole, 'DIFFERENCE')

for key in keys:
   add_modifier_boolean ('Base', key, 'UNION')

add_cavity (
   'Base',
   positions ['J3']['right'] + WALL, positions ['J4']['bottom'] + WALL,
   positions ['J1']['left'] - WALL, positions ['DPSM1']['top'] - WALL,
)

add_cavity (
   'Base',
   positions ['J3']['right'] + WALL, positions ['DPSM1']['bottom'] + WALL,
   positions ['J1']['left'] - WALL, positions ['DPSM3']['top'] - WALL,
)

add_cavity (
   'Base',
   positions ['J3']['right'] + WALL, positions ['DPSM3']['bottom'] + WALL,
   positions ['J1']['left'] - WALL, y_max + WALL + 1,
)


add_cavity (
   'Base',
   positions ['J3']['right'] + WALL, positions ['DPSM1']['top'] - WALL - 1,
   positions ['DPSM1']['left'] - WALL, positions ['DPSM1']['bottom'] + WALL + 1,
)

add_cavity (
   'Base',
   positions ['DPSM1']['right'] + WALL, positions ['DPSM1']['top'] - WALL - 1,
   positions ['DPSM2']['left'] - WALL, positions ['DPSM1']['bottom'] + WALL + 1,
)

add_cavity (
   'Base',
   positions ['DPSM2']['right'] + WALL, positions ['DPSM1']['top'] - WALL - 1,
   positions ['J1']['left'] - WALL, positions ['DPSM1']['bottom'] + WALL + 1,
)

add_cavity (
   'Base',
   positions ['J3']['right'] + WALL, positions ['DPSM3']['top'] - WALL - 1,
   positions ['DPSM3']['left'] - WALL, positions ['DPSM3']['bottom'] + WALL + 1,
)

add_cavity (
   'Base',
   positions ['DPSM3']['right'] + WALL, positions ['DPSM3']['top'] - WALL - 1,
   positions ['DPSM4']['left'] - WALL, positions ['DPSM4']['bottom'] + WALL + 1,
)

add_cavity ('Base', 46, 59, 54, 61)

add_cavity (
   'Base',
   -10, positions ['J7']['bottom'] + WALL,
   positions ['J7']['right'] + WALL + 1, positions ['J5']['top'] - WALL,
)

add_cavity (
   'Base',
   positions ['J10']['left'] - WALL - 1, positions ['J10']['bottom'] + WALL,
   positions ['J10']['right'] + 1, positions ['J2']['top'] - WALL,
)

add_box ('Compspace1',
   positions ['J3']['right'] - 0.1, positions ['J3']['top'],
   WALL + 1, positions ['J7']['bottom'] - positions ['J3']['top'],
   -8, - BASE_HEIGHT * 0.5 + 1, 0
)
add_modifier_boolean ('Base', 'Compspace1', 'DIFFERENCE')

add_box ('Compspace2',
   positions ['J4']['left'], positions ['J4']['bottom'] - 0.1,
   positions ['J12']['right'] - positions ['J4']['left'], WALL + 1,
   -8, - BASE_HEIGHT * 0.5 + 1, 0
)
add_modifier_boolean ('Base', 'Compspace2', 'DIFFERENCE')


bpy.ops.object.select_all (action='DESELECT')

bpy.ops.object.select_pattern (pattern='Base')

filename = 'soldering-jig-c%d.stl' % (CLEARANCE * 1000)

bpy.ops.export_mesh.stl (
   filepath=os.path.join (PATH_ARTIFACTS, filename),
   use_selection=True,
   use_mesh_modifiers=True,
)

bpy.ops.wm.quit_blender ()
