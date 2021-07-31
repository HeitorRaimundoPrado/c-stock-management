#include "manage.h"


void stockManagementUpdate(int productIndex, char* attr, char* newValue) {
    return;
}
void stockManagementDelete(int productIndex) {
    return;
}
void stockManagementSet(char* attr, char* newValue) {
    return;
}
void stockManagementGet(int index, char* out, int lengthOut, char* data, int sizeOfData){
   int i = 0;
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
   for (i = 0; i <= index && row != NULL; i++){
       row = strtok(NULL, "\n");
   }
   if (row == NULL) {
       strcpy(out, "Invalid Index");
       return;
   }
   if (strlen(row) < lengthOut){
       strcpy(out, row);
   }
   free(dataCopy);
}
