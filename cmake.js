var fs = require('fs');

var sourceDir = './source';
var cmakeFilename = 'CMakeLists.txt';

fs.readdir(sourceDir, function (err, files)
{
    fs.writeFile(sourceDir + '/' + cmakeFilename, "CMAKE_MINIMUM_REQUIRED (VERSION 2.6)");

    for(var i in files)
    {
        (function(dir, filename)
        {
            var fullFilename = dir + '/' + filename;

            fs.stat(fullFilename, function (err, stats) {
                if (stats !== undefined)
                {
                    if (stats.isDirectory())
                    {
                        var txt = "CMAKE_MINIMUM_REQUIRED (VERSION 2.6)";
                        fs.writeFile(fullFilename + '/' + 'CMakeLists.txt', txt);
                    }
                }
                else
                {
                    process.stdout.write(fullFilename + " : Error" + '\n');
                }
            });
        })(sourceDir, files[i]);
    }
});