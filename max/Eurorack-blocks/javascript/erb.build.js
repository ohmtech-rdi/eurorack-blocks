const maxApi = require("max-api");

const path = require('path');
const { spawn } = require("child_process");

const PATH_EURORACK_BLOCKS = path.dirname(path.dirname(path.dirname(__dirname)));
const PATH_ERBB = path.join(PATH_EURORACK_BLOCKS, 'build-system', 'scripts', 'erbb');

function erbb(modulePath, ...command) {
   const cmd = [PATH_ERBB, ...command];

   return new Promise((resolve, reject) => {
      const p = spawn('python3', cmd, { cwd: modulePath });

      try {
         p.stdout.on("data", data => {
            maxApi.post(`${data}`);
            maxApi.outlet(`${data}`);
         });
         p.stderr.on("data", data => {
            maxApi.post(`Error: ${data}`);
            maxApi.outlet(`Error: ${data}`);
         });
         p.on("close", code => {
            maxApi.post(`child process exited with code ${code}`);
            resolve();
         });
      } catch (e) {
         reject(e);
      }
   });
}

const build = async (modulePath) => {
   maxApi.post("Build starting");

   args = process.argv.slice(2)
   modulePath = args [0]
   maxApi.post(`module: ${modulePath}`);

   try {
      maxApi.post(`Configuring...`);
      await erbb(modulePath, 'configure');
      maxApi.post(`Building...`);
      await erbb(modulePath, 'build', 'simulator');
      maxApi.outlet('Done');
   } catch(e) {
      maxApi.post(e.message ? e.message : e, maxApi.POST_LEVELS.ERROR);
   }
};

build();
