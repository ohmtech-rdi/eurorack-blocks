
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

function preprocess() {
   var patcher = findTopPatcher();
   var modulePath = makeModulePath(patcher.filepath);

   outlet(0, 'script', 'start', modulePath);
}
