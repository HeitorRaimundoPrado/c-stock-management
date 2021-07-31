#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "manage.h"

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Wrong usage\n");
        exit(1);
    }
    char pathToCsv[50];
    strcpy(pathToCsv, argv[1]);
    FILE *readPointer = fopen(pathToCsv, "r");
    
    if (readPointer == NULL) {
        fprintf(stderr, "Unable to open file!\n");
        exit(1);
    }

    char *data = (char *) malloc(50 * sizeof(char));
    if (data == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
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
            if (data == NULL){
                fprintf(stderr, "Out of memory!\n");
                exit(1);
            }
            sizeOfData*=2;
            data[i] = c;
            i++;
        }
    }
    fclose(readPointer);
    data[i] = '\0';
    int lengthOfData = i;
    char *attr = malloc(i*sizeof(char)+1);
    if (attr == NULL){
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    strcpy(attr, data);
    char *attributes = strtok(attr, "\n");
    bool q = false;
    while (!q) {
        int opt;
        printf("Usage:\n1. Update\n2. Delete\n3. Add\n4. Get\n5. Quit\n");
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
                char *newAttr = strtok(attributes, ",");
                char value[100];
                while (newAttr != NULL) {
                    printf("%s: ", newAttr);
                    stockManagementSet(newAttr, value);
                    newAttr = strtok(NULL, ",");
                }
                break;
            }
            case 4:
            {
                int productIndex;
                char output[100];
                scanf("%d", &productIndex);
                stockManagementGet(productIndex, output, 100, data, lengthOfData);
                puts(output);
                break;
            }
            case 5:
            {
                q = true;
                break;
            }
        }
    }
    free(attributes);
    free(data);
}
