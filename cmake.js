var fs = require('fs');

var sourceDir = './source';
var cmakeFilename = 'CMakeLists.txt';
var cmakeVersion = 2.6;

var subDirs = [];

var dirLevel = 0;
subDirs[dirLevel] = [sourceDir];

while (true) {
    var nextDirLevel = dirLevel + 1;
    subDirs[nextDirLevel] = [];

    for (var i in subDirs[dirLevel]) {
        var file = subDirs[dirLevel][i];

        var files = fs.readdirSync(file);
        for (var j in files) {
            var stats = fs.statSync(file + '/' + files[j]);

            if (stats.isDirectory()) {
                subDirs[nextDirLevel].push(file + '/' + files[j]);
            }
        }
    }

    if (subDirs[nextDirLevel].length == 0) {
        delete subDirs[nextDirLevel];
        break;
    }
    ++dirLevel;
}

console.log(subDirs);

for (var i in subDirs)
{
    var dirs = subDirs[i];

    for(var j in dirs)
    {
        var dir = dirs[j];
        fs.writeFile(dir + '/' + cmakeFilename, "asdf");
    }
}

/*
fs.readdir(sourceDir, function (err, files) {
    var sourceTxt = 'CMAKE_MINIMUM_REQUIRED (VERSION ' + cmakeVersion + ')\n';


    for (var i in files) {
        var fullFilename = sourceDir + '/' + files[i];

        var stats = fs.statSync(fullFilename);
        if (stats.isDirectory()) {
            var txt = 'CMAKE_MINIMUM_REQUIRED (VERSION ' + cmakeVersion + ')\n';
            fs.writeFile(fullFilename + '/' + 'CMakeLists.txt', txt);
        };

        if (stats.isDirectory()) {
            sourceTxt += 'ADD_SUBDIRECTORY("${TIMEENGINE_SOURCE_DIR}/' + files[i] + '")\n';
        }
    }

    fs.writeFile(sourceDir + '/' + cmakeFilename, sourceTxt);
});*/