function main() 
{
    writeLanguageFiles();
}

function writeLanguageFiles()
{
    let folder = vuengine.getWorkspaceRoot();

    let languages = vuengine.getProjectConfig('languages');

    for (let stringId in languages.strings) {
        for (let languageId in languages.strings[stringId]) {
            languages.strings[stringId][languageId] = convertToHexRepresentation(languages.strings[stringId][languageId]);
        }
    }
    for (let languageId in languages.languages) {
        languages.languages[languageId]['name'] = convertToHexRepresentation(languages.languages[languageId]['name']);
    }

    templates.renderToFile(
        __dirname + '/templates/Languages.c.nj',
        folder + '/assets/languages/Languages.c',
        languages
    );

    templates.renderToFile(
        __dirname + '/templates/Languages.h.nj',
        folder + '/source/assets/Languages.h',
        languages
    );

    for (let key of Object.keys(languages['languages'])) {
        templates.renderToFile(
            __dirname + '/templates/Language_xx.c.nj',
            folder + '/assets/languages/Language_' + key + '.c',
            vuengine.mergeRecursively(languages, {'languageKey': key}),
            {
                encoding: 'latin1'
            }
        );
    }
}

// convert all hiragana chars of a string to hex representations
function convertToHexRepresentation(string) {
    let convertedString = '';
    for (var i=0, len=string.length; i<len; i++) {
        if (string.charCodeAt(i) > 12352 && string.charCodeAt(i) <= 12415 ) {
            let code = string.charCodeAt(i) - 12224;
            convertedString += '\\x' + code.toString(16);
        } else {
            convertedString += string[i];
        }
    }
    return convertedString;
}