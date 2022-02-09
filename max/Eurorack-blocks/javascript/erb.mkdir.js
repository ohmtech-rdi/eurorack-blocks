const maxApi = require("max-api");
const fs = require('fs')

try {
   args = process.argv.slice(2)
   modulePath = args [0]
   artifactsDir = modulePath + 'artifacts'

   if (fs.existsSync(artifactsDir)) {
      maxApi.post('artifacts already exists, skipping.');
   } else {
      maxApi.post(`creating ${artifactsDir} folder`);
      fs.mkdirSync(artifactsDir);
   }

   maxApi.outlet('bang');
} catch(e) {
   maxAPI.post(e.message ? e.message : e, maxAPI.POST_LEVELS.ERROR);
}
