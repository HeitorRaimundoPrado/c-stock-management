#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "manage.h"
#include "log.h"
#include "csmconfig.h"


#ifndef C_STOCK_MANAGER_BUILD_TYPE
#define C_STOCK_MANAGER_BUILD_TYPE "Release"
#endif

#ifndef LOG_FILE_PATH
#define LOG_FILE_PATH ""
#endif

#define NUM_OF_CONFIGS 2

int main(int argc, char *argv[]) {
    enum main_opt {update=1, delete, add, get, trade, quit};
    // Read config file:
    char pathToCsv[50] = {0}, pathToTradesRegister[50] = {0};
    char ** configOptions = malloc(NUM_OF_CONFIGS * sizeof(char*));
    if (configOptions == NULL) {
        fprintf(stderr, "Out of memory!!\n");
        exit(1);
    }

    readConfigFile("csm.cfg", &configOptions);
    if(strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0){
        char allConfigs[1500] = {0};
        char currConfig[100];
        for (int i = 0; i < NUM_OF_CONFIGS; i++) {
            sprintf(currConfig, "config[%d] = ", i);
            strcat(allConfigs, currConfig);
            strcat(allConfigs, configOptions[i]);
            strcat(allConfigs, "\n");
        }
        csmLog(allConfigs, NULL, __FILE__, __LINE__);
    }
    if (strcmp(configOptions[0], "") != 0) {
        strcpy(pathToCsv, configOptions[0]);
    }

    if (strcmp(configOptions[1], "") != 0) {
        strcpy(pathToTradesRegister, configOptions[1]);
    }


    for (int i = 0; i < 2; i++) {
        free(configOptions[i]);
    }

    free(configOptions);

    if (argc == 2) {
        strcpy(pathToCsv, argv[1]);
    }
    else if (argc == 3){
        strcpy(pathToCsv, argv[1]);
        strcpy(pathToTradesRegister, argv[2]);

    }

    char *data = (char *) malloc(50 * sizeof(char));

    if (data == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    unsigned long long lengthOfData = 0;
    unsigned long long sizeOfData = 50;
    stockManagementRead(pathToCsv, &data, &lengthOfData, &sizeOfData);
    char *attr = malloc(lengthOfData*sizeof(char)+1);
    if (attr == NULL){
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    strcpy(attr, data);
    char *attributes = strtok(attr, "\n");
    bool q = false;
    while (!q) {

        if (strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0) { 
            csmLog(data, "Data read from file: ", __FILE__, __LINE__);
        }

        int opt;
        printf("\nUsage:\n1. Update\n2. Delete\n3. Add\n4. Get\n5. Trade\n6. Quit.\n\n");
        char optStr[10];
        fgets(optStr, 10, stdin);
        sscanf(optStr, "%d", &opt);
        switch(opt) {
            case update:
            {
                // int productIndex;
                char newValue[100], atribute[100], productIndex[10];
                printf("Product Index: ");
                fgets(productIndex, 10, stdin);
                productIndex[strcspn(productIndex, "\n")] = 0;

                // scanf("%d", &productIndex);
                printf("Attribute: ");
                fgets(atribute, 100, stdin);
                atribute[strcspn(atribute, "\n")] = 0;

                printf("New Value: ");
                fgets(newValue, 100, stdin);
                newValue[strcspn(newValue, "\n")] = 0;

                stockManagementUpdate(productIndex, atribute, newValue, attributes, data, pathToCsv);

                stockManagementRead(pathToCsv, &data, &lengthOfData, &sizeOfData);
                break;
            }

            case delete:
            {
                char productIndex[10];
                printf("Product index: ");
                fgets(productIndex, 10, stdin);

                productIndex[strcspn(productIndex, "\n")] = 0;

                stockManagementDelete(productIndex, data, pathToCsv);
                stockManagementRead(pathToCsv, &data, &lengthOfData, &sizeOfData);
                break;
                
            }

            case add:
            {
                // for each attribute get new value
                char *attributesCopy = malloc(strlen(attributes)+1);
                if (attributesCopy == NULL) {
                    fprintf(stderr, "Out of memory!\n");
                    exit(1);
                }

                strcpy(attributesCopy, attributes);
                char *newAttr = strtok(attributesCopy, ",");
                char value[100];
                FILE *writePointer = fopen(pathToCsv, "a");
                while (newAttr != NULL) {
                    printf("%s: ", newAttr);
                    fgets(value, 100, stdin);
                    stockManagementSet(value, writePointer);
                    newAttr = strtok(NULL, ",");
                }

                putc('\n', writePointer);
                fclose(writePointer);
                free(attributesCopy);
                stockManagementRead(pathToCsv, &data, &lengthOfData, &sizeOfData);
                break;
            }

            case get:
            {
                char output[100], productIndex[100];

                printf("Product Index: ");
                fgets(productIndex, 100, stdin);

                productIndex[strcspn(productIndex, "\n")] = 0;

                stockManagementGet(productIndex, output, 100, data, lengthOfData);
                puts(output);
                break;
            }

            case trade:
            {
                char productIndex[10];
                int tradeOpt, quantity;

                printf("\n1. Sale\n2. Purchase\n");
                fgets(productIndex, 10, stdin);
                sscanf(productIndex, "%d", &tradeOpt);

                printf("Quantity: ");
                fgets(productIndex, 10, stdin);
                sscanf(productIndex, "%d", &quantity);

                printf("\nProduct Index: ");
                fgets(productIndex, 10, stdin);
                productIndex[strcspn(productIndex, "\n")] = 0;

                stockManagementTrade(tradeOpt, quantity, productIndex, pathToTradesRegister, pathToCsv, data, sizeOfData);
                    stockManagementRead(pathToCsv, &data, &lengthOfData, &sizeOfData);
                break;

            }

            case quit:
            {
                q = true;
                break;
            }
        }
    }
    free(attributes);
    free(data);
    return 0;
}
