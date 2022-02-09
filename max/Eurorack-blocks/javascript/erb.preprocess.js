
autowatch = 1;
inlets = 1;
outlets = 1;

function bang() {
   preprocess();
}

function findTopPatcher() {
   var patcher = this.patcher;
   while (patcher.parentpatcher) {
      patcher = patcher.parentpatcher;
   }
   return patcher;
}

function makeModulePath(filePath) {
   b = filePath.indexOf('/');
   e = filePath.lastIndexOf('/');
   return filePath.substr(b, e - b) + '/';
}

function findGenObject(patcher) {
   var obj = patcher.firstobject;
   while (obj) {
      if (obj.maxclass.toString() == "gen~") {
         return obj;
      }
      obj = obj.nextobject;
   }
   return null
}

function preprocess() {
   var patcher = findTopPatcher();

   gen_obj = findGenObject(patcher);
   if (!gen_obj)
   {
      error("eurorack-blocks: No gen~ object found\n");
      patcher.message("write");
      return false;
   }

   var modulePath = makeModulePath(patcher.filepath);
   gen_obj.message("exportname", "module_max");
   gen_obj.message("exportfolder", modulePath + 'artifacts/');
   gen_obj.message("exportcode");

   outlet(0, 'script', 'start', modulePath);
}
