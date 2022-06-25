##############################################################################
#
#     manifest.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os



class Manifest:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      path_json = os.path.join (path, 'plugin.json')

      with open (path_json, 'w', encoding='utf-8') as file:
         file.write ('{\n')
         file.write ('   "slug": "ErbPlugin%s",\n' % root.modules [0].name)
         file.write ('   "name": "Erb Plugin",\n')
         file.write ('   "version": "2.0.0",\n')
         file.write ('   "license": "proprietary",\n')
         file.write ('   "brand": "Erb",\n')
         file.write ('   "author": "Erb",\n')
         file.write ('   "authorEmail": "",\n')
         file.write ('   "authorUrl": "https://github.com/ohmtech-rdi/eurorack-blocks",\n')
         file.write ('   "pluginUrl": "https://github.com/ohmtech-rdi/eurorack-blocks",\n')
         file.write ('   "manualUrl": "https://github.com/ohmtech-rdi/eurorack-blocks",\n')
         file.write ('   "sourceUrl": "https://github.com/ohmtech-rdi/eurorack-blocks",\n')
         file.write ('   "donateUrl": "",\n')
         file.write ('   "changelogUrl": "",\n')
         file.write ('   "modules": [\n')

         for index, module in enumerate (root.modules):
            file.write ('      {\n')
            file.write ('         "slug": "%s",\n' % module.name)
            file.write ('         "name": "%s",\n' % module.name)
            file.write ('         "description": "%s",\n' % module.name)
            file.write ('         "tags": [ "Digital", "Hardware" ]\n')
            if index == len (root.modules) - 1:
               file.write ('      }\n')
            else:
               file.write ('      },\n')

         file.write ('   ]\n')
         file.write ('}\n')
