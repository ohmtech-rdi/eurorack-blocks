##############################################################################
#
#     c_cpp_properties.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))



class CCppProperties:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_template = os.path.join (PATH_THIS, 'c_cpp_properties_template.json')
      path_dst = os.path.join (path, '.vscode', 'c_cpp_properties.json')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%           includes_simulator%', self.generate_module_includes_simulator (path, module))
      template = template.replace ('%           includes_firmware%', self.generate_module_includes_firmware (path, module))
      template = template.replace ('%           defines.entities,%', self.generate_module_defines (module))

      with open (path_dst, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_module_includes_simulator (self, path, module):

      path_artifacts = os.path.join (path, 'artifacts')

      paths = []
      paths.append (path)
      paths.append (os.path.join (PATH_ROOT, 'include'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'vcv-rack-sdk', 'include'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'vcv-rack-sdk', 'dep', 'include'))

      for base in module.bases:
         paths.append (base.path)

      return ',\n'.join (map (lambda x: '            "${workspaceRoot}/%s"' % os.path.relpath (x, path).replace ('\\', '/'), paths))


   #--------------------------------------------------------------------------

   def generate_module_includes_firmware (self, path, module):

      path_artifacts = os.path.join (path, 'artifacts')

      paths = []
      paths.append (path)
      paths.append (os.path.join (PATH_ROOT, 'include'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'src'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'src', 'sys'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'src', 'usbd'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'src', 'usbh'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Drivers', 'CMSIS', 'Include'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Drivers', 'CMSIS', 'Device', 'ST', 'STM32H7xx', 'Include'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Drivers', 'CMSIS', 'DSP', 'Include'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Drivers', 'STM32H7xx_HAL_Driver', 'Inc'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Drivers', 'STM32H7xx_HAL_Driver', 'Inc', 'Legacy'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Middlewares', 'ST', 'STM32_USB_Device_Library', 'Core', 'Inc'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Middlewares', 'ST', 'STM32_USB_Device_Library', 'Class', 'CDC', 'Inc'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Middlewares', 'ST', 'STM32_USB_Host_Library', 'Core', 'Inc'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Middlewares', 'ST', 'STM32_USB_Host_Library', 'MSC', 'CDC', 'Inc'))
      paths.append (os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'Middlewares', 'Third_Party', 'FatFs', 'src'))

      for base in module.bases:
         paths.append (base.path)

      return ',\n'.join (map (lambda x: '            "${workspaceRoot}/%s"' % os.path.relpath (x, path).replace ('\\', '/'), paths))


   #--------------------------------------------------------------------------

   def generate_module_defines (self, module):

      define_map = {
         'erb_BUFFER_SIZE': '48',
         'erb_SAMPLE_RATE': '48014',
         'erb_MIDI_MESSAGE_SIZE': '128',
      }

      for define in module.defines:
         define_map [define.key] = define.value

      lines = ''
      for key, value in define_map.items ():
         lines += '            "%s=%s",\n' % (key, value)

      return lines
