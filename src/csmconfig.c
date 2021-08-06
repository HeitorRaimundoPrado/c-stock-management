#include "csmconfig.h"

void readConfigFile (char* pathToConfig, char*** returnStrArr) {
    char option[30], value[30], buff[62];
    FILE *readPointer = fopen(pathToConfig, "r");
    if (readPointer == NULL) {
        fprintf(stderr, "Unable to open config file\n");
        exit(1);
    }

    for (int i = 0; i < 2; i++) {
        (*returnStrArr)[i] = calloc(30, sizeof(char));
    }
    while (1) {
        fgets(buff, 62, readPointer);
        if (feof(readPointer)) {
            break;
        }

        sscanf(buff, "%29s %29s", option, value);
        if (strcmp(option, "pathStock") == 0) {
            strcpy((*returnStrArr)[0], value);
        } 

        else if (strcmp(option, "pathRegister") == 0) {
            strcpy((*returnStrArr)[1],  value);
        }
    }
}
