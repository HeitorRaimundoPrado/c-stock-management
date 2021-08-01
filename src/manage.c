#include "manage.h"

void stockManagementTrade(int opt, int quantity, int productIndex) {
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
            (*i)++;
        }
        else {
            *data = (char*)realloc(*data, (*sizeOfData)*2*sizeof(char));
            if (*data == NULL){
                fprintf(stderr, "Out of memory!\n");
                exit(1);
            }
            (*sizeOfData)*=2;
            (*data)[(*i)] = c;
            (*i)++;
        }
    }
    fclose(readPointer);
    (*data)[(*i)] = '\0';
}

void stockManagementUpdate(int productIndex, char* attr, char* newValue) {
    return;
}
void stockManagementDelete(char *productIndex, unsigned long long sizeOfData, char *data, char *pathToFile) {
   if (productIndex < 0) {
       fprintf(stderr, "Invalid index\n");
       return;
   }
   char *dataCopy = malloc(sizeOfData*sizeof(char)+1);
   if (dataCopy == NULL) {
       fprintf(stderr, "Out of memory!\n");
       exit(1);
   }
   strcpy(dataCopy, data);
   char *row = strtok(dataCopy, "\n");
   unsigned long lengthOfIndex = strlen(productIndex)-1;
   char *toWrite = calloc(strlen(data)+1, sizeof(char));
   if (toWrite == NULL) {
       fprintf(stderr, "Out of memory!\n");
       exit(1);
   }
   bool indexExistent = false;
   while (row != NULL){
       int currentIndexLength = strcspn(row, ",");
       bool currentIsIndex = true;
       if (currentIndexLength != lengthOfIndex) {
           currentIsIndex = false;
       }
       else {
           for (int i = 0; i < currentIndexLength; i++){
               if (row[i] != productIndex[i]) {
                   currentIsIndex = false;
                   break;
               }
           }
       }
       if (currentIsIndex){
           indexExistent = true;
           row = strtok(NULL, "\n");
           continue;
       }
       strcat(toWrite, row);
       strcat(toWrite, "\n");
//       puts("\ntoWrite: ");
//       puts(toWrite);

       row = strtok(NULL, "\n");
   }
   if (!indexExistent) {
       fprintf(stderr, "Index inexistent\n");
       free(toWrite);
       free(dataCopy);
       return;
   }
   FILE *writePointer = fopen(pathToFile, "w");
   fputs(toWrite, writePointer);
   fclose(writePointer);
   free(dataCopy);
   free(toWrite);
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
void stockManagementGet(char* index, char* out, int lengthOut, char* data, int sizeOfData){
   if (index < 0) {
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
   unsigned long lengthOfIndex = strlen(index)-1;
   while (row != NULL){
       int currentIndexLength = strcspn(row, ",");
       bool currentIsIndex = true;
       if (currentIndexLength != lengthOfIndex) {
           currentIsIndex = false;
       }
       else {
           for (int i = 0; i < currentIndexLength; i++){
               if (row[i] != index[i]) {
                   currentIsIndex = false;
                   break;
               }
           }
       }
       if (currentIsIndex){
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
