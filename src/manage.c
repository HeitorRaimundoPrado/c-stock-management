#include "manage.h"

void stockManagementTrade(int opt, int quantity, char* productIndex) {
    if (opt == 1) {
    }
    else {
        
    }
    return;
}

void stockManagementRead(char* pathToFile, char **data, unsigned long long *i, unsigned long long *sizeOfData){
    memset(*data, 0, *i);
    *i = 0;
    FILE *readPointer = fopen(pathToFile, "r");
    
    if (readPointer == NULL) {
        fprintf(stderr, "Unable to open file!\n");
        exit(1);
    }

    char c;
    while (1) {
        c = fgetc(readPointer);
        if (feof(readPointer)) {
            break;
        }

        if ((*i) < (*sizeOfData)-1) {
            (*data)[(*i)] = c;
        }

        else {
            *data = (char*)realloc(*data, (*sizeOfData)*2*sizeof(char));
            if (*data == NULL){
                fprintf(stderr, "Out of memory!\n");
                exit(1);
            }
            (*sizeOfData)*=2;
            (*data)[(*i)] = c;
        }
        (*i)++;
    }
    fclose(readPointer);
    (*data)[(*i)] = '\0';
}

void stockManagementUpdate(char* productIndex, char* attr, char* newValue, char* allAttributes, char* data, char* pathToFile) {
    char *attrCopy = malloc(strlen(allAttributes));
    if (attrCopy == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    strcpy(attrCopy, allAttributes);
    char *currAttr = strtok(attrCopy, ",");
    int indexOfAttr = 0;

    while (currAttr != NULL && strcmp(currAttr, attr) != 0) {
        currAttr = strtok(NULL, ",");
        indexOfAttr++;
    }

    if (currAttr == NULL) {
        fprintf(stderr, "Attribute inexistent\n");
        return;
    }

    char *toWrite = calloc(strlen(data)+strlen(newValue)+40, sizeof(char));
    char *row = strtok(data, "\n");
    bool wroteNewValue = false;

    while (row != NULL){
        if (strlen(productIndex) == strcspn(row, ",") && strncmp(productIndex, row, strcspn(row, ",")) == 0){
            int currAttr = 0;

            for(unsigned long i = 0; i < strlen(row); i++) {
                if (row[i] == ',' ) {
                    currAttr++;
                }
                if (currAttr == indexOfAttr && !wroteNewValue) {
                    strcat(toWrite, ",");
                    strcat(toWrite, newValue);
                    wroteNewValue = true;
                }
                else if (currAttr != indexOfAttr) {
                    strncat(toWrite, &row[i], 1);
                }
            }

            strcat(toWrite, "\n");
            row = strtok(NULL, "\n");
            continue;
        }

        else {
            strcat(toWrite, row);
            strcat(toWrite, "\n");
        }
        row = strtok(NULL, "\n");
    }

    if (!wroteNewValue) {
        fprintf(stderr, "Index inexistent!\n");
        free(toWrite);
        return;
    }

    FILE *writePointer = fopen(pathToFile, "w");
    if (writePointer == NULL) {
        fprintf(stderr, "Unable to open file!\n");
        free(toWrite);
        exit(1);
    }
    fputs(toWrite, writePointer);
    fclose(writePointer);
    free(toWrite);
}

void stockManagementDelete(char *productIndex, char *data, char *pathToFile) {
   if (atoi(productIndex) < 0) {
       fprintf(stderr, "Invalid index\n");
       return;
   }

   char *toWrite = calloc(strlen(data)+1, sizeof(char));
   char *row = strtok(data, "\n");
   if (toWrite == NULL) {
       fprintf(stderr, "Out of memory!\n");
       exit(1);
   }

   bool indexExistent = false;
   while (row != NULL){
       if (strlen(productIndex)-1 == strcspn(row, ",") && strncmp(productIndex, row, strcspn(row, ",")) == 0){
           indexExistent = true;
           row = strtok(NULL, "\n");
           continue;
       }
       strcat(toWrite, row);
       strcat(toWrite, "\n");
       row = strtok(NULL, "\n");
   }

   if (indexExistent == false) {
       fprintf(stderr, "Index inexistent\n");
       free(toWrite);
       return;
   }

   FILE * wP = fopen(pathToFile, "w+");
   fputs(toWrite, wP);
   free(toWrite);
   fclose(wP);
   return;
}

void stockManagementSet(char* newValue, FILE* writePointer) {
    for (int i = 0; newValue[i] != '\0'; i++){
        if (newValue[i] != '\n'){
            putc(newValue[i], writePointer);
        } 
    }
    putc(',', writePointer);
    return;
}

void stockManagementGet(char* index, char* out, unsigned long lengthOut, char* data, int sizeOfData){
   if (atoi(index) < 0) {
       strcpy(out, "Invalid index");
       return;
   }

   char *dataCopy = malloc(sizeOfData*sizeof(char)+1);

   if (dataCopy == NULL) {
       fprintf(stderr, "Out of memory!\n");
       exit(1);
   }

   strcpy(dataCopy, data);
   char *row = strtok(dataCopy, "\n");

   while (row != NULL){
       if (strlen(index)-1 == strcspn(row, ",") && strncmp(index, row, strcspn(row, ",")) == 0){ 
           break;
       }
       row = strtok(NULL, "\n");
   }

   if (row == NULL) {
       strcpy(out, "Index inexistent");
       return;
   }

   if (strlen(row) < lengthOut){
       strcpy(out, row);
   }
   free(dataCopy);
}
