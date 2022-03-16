#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define EXPECTED_NUMBER_OF_ARGUMENTS 2
#define MAX_LINE_LENGTH 1000

// ERROR CODES
#define INVALID_NUMBER_OF_ARGUMENTS_ERROR_CODE 1
#define COULD_NOT_READ_FILE_ERROR_CODE 2

bool doesWordMatch(const char *fileName, char *searchWord, int charCount) {
    int indexCount = 0;

    for (int i = 0; i < strlen(searchWord); i++) {
        if (fileName[charCount] != searchWord[indexCount]) {
            return false;
        }
        charCount++;
        indexCount++;
    }
    return true;

}

FILE *makeReadFile(char *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Could not open file");
        exit(COULD_NOT_READ_FILE_ERROR_CODE);
    }

    return file;
}

bool searchFileForWord(char *fileName, char *searchWord) {
    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;
    bool wordFound = false;

    FILE *file = makeReadFile(fileName);

    while (!wordFound && fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        lineNumber++;
        int lineLength = strlen(line);
        int characterCount = 0;

        while (!wordFound && characterCount < lineLength ) {
            if (doesWordMatch(line, searchWord, characterCount) == true) {
                characterCount++;
                printf("Line: %d, character: %d", lineNumber, characterCount);
                wordFound = true;
            }
            characterCount++;
        }

    }
    fclose(file);
    return wordFound;

}

void validateNumberOfArguments(int argc) {
    if (argc != (EXPECTED_NUMBER_OF_ARGUMENTS + 1)) {
        perror("Program requires exactly two arguments");
        exit(INVALID_NUMBER_OF_ARGUMENTS_ERROR_CODE);
    }
}

int main(int argc, char *argv[]) {

    validateNumberOfArguments(argc);

    bool isWordFound = searchFileForWord(argv[1], argv[2]);

    if (!isWordFound) {
        printf("Not Found!");
    }

    return 0;
}
