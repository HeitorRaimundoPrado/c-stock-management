#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manage.h"

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Wrong usage\n");
        exit(1);
    }
    char pathToCsv[50];
    strcpy(pathToCsv, argv[1]);
    FILE *readPointer = fopen(pathToCsv, "r");
    
    char *data = (char *) malloc(50 * sizeof(char));
    char c;
    unsigned long long i = 0, sizeOfData = 50;
    while (1) {
        c = fgetc(readPointer);
        if (feof(readPointer)) {
            break;
        }
        if (i < sizeOfData-1) {
            data[i] = c;
            i++;
        }
        else {
            data = (char*)realloc(data, sizeOfData*2*sizeof(char));
            sizeOfData*=2;
            data[i] = c;
            i++;
        }
    }
    fclose(readPointer);
    data[i] = '\0';
    char *attributes = strtok(data, "\n");

    while (1) {
        int opt;
        scanf("%d", &opt);
        switch(opt) {
            case 1:
            {
                int productIndex;
                char newValue[100], atribute[100];
                scanf("%d", &productIndex);
                fgets(newValue, 100, stdin);
                fgets(atribute, 100, stdin);
                stockManagementUpdate(productIndex, atribute, newValue);
                break;
            }
            case 2:
            {
                int productIndex;
                scanf("%d", &productIndex);
                stockManagementDelete(productIndex);
                break;
                
            }
            case 3:
            {
                // for each attribute get new value
                char *attr = strtok(attributes, ",");
                char value[100];
                while (attr != NULL) {
                    printf("%s: ", attr);
                    stockManagementSet(attr, value);
                    attr = strtok(NULL, ",");
                }
            }
            case 4:
            {
                int productIndex;
                char output[100];
                scanf("%d", &productIndex);
                stockManagementGet(productIndex, output, 100,data);
                puts(output);
            }
        }
    }
    free(data);
}
