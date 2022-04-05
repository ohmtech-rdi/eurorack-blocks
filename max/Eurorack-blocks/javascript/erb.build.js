const maxApi = require("max-api");

const { spawn } = require("child_process");

maxApi.post("Build starting");

let msgs = []

try {
   args = process.argv.slice(2)
   modulePath = args [0]
   maxApi.post(`module: ${modulePath}`);
   const build = spawn(
      process.env.SHELL, ['-l', '-c', 'erbb configure && erbb build simulator'],
      { cwd: modulePath }
   )

   build.stdout.on('data', (data) => {
      maxApi.post(`${data}`);
      maxApi.outlet(`${data}`);
   });

   build.stderr.on('data', (data) => {
      maxApi.post(`Error: ${data}`);
      maxApi.outlet(`Error: ${data}`);
   });

   build.on('close', (code) => {
      maxApi.post(`child process exited with code ${code}`);
      maxApi.outlet('Done');
   });

} catch(e) {
   maxAPI.post(e.message ? e.message : e, maxAPI.POST_LEVELS.ERROR);
}
