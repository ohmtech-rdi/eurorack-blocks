const maxApi = require("max-api");

const path = require('path');
const { spawn } = require("child_process");

const PATH_EURORACK_BLOCKS = path.dirname(path.dirname(path.dirname(__dirname)));

function erbb(modulePath, ...command) {
   const erbb_command = ['erbb', ...command];
   script_arg = `${erbb_command.join(' ')}`

   return new Promise((resolve, reject) => {
      // Launch the shell using the user profile, to make sure that 'erbb'
      // is executed like it is in a terminal (as Max replaces for example
      // the path with its own).

      let command = null;
      let args = null;

      if (process.platform === 'win32') {
         command = 'C:/Program Files/Git/usr/bin/env.exe'
         args = ['MSYSTEM=MINGW64', '/usr/bin/bash', '-l', '-c', script_arg]

      } else {
         // For bash, zsh and fish, '-l' is more or less a login shell
         // This ensures that 'erbb' is launched as it is in a terminal, in particular
         // for the PATH that Max replaces with its own.

         command = process.env.SHELL;

         if (command.includes('bash')) {
            args = ['--login', '-c', script_arg]
         } else if (command.includes('zsh')) {
            args = ['--login', '-i', '-c', script_arg]
         } else if (command.includes('fish')) {
            args = ['--login', '-c', script_arg]
         }
      }

      const p = spawn(command, args, { cwd: modulePath });

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
