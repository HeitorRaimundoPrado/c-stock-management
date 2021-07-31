#include "manage.h"


void stockManagementUpdate(int productIndex, char* attr, char* newValue) {
    return;
}
void stockManagementDelete(int productIndex) {
    return;
}
void stockManagementSet(char* newValue, FILE* writePointer) {
    for (int i = 0; newValue[i] != '\0'; i++){
        putc(newValue[i], writePointer);
    } 
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
   while (row != NULL){
       int currentIndexLength = strcspn(row, ",");
       bool currentIsIndex = true;
       for (int i = 0; i < currentIndexLength; i++){
           if (row[i] != index[i]) {
               currentIsIndex = false;
               break;
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
