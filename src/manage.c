#include "manage.h"


void stockManagementUpdate(int productIndex, char* attr, char* newValue);
void stockManagementDelete(int productIndex);
void stockManagementSet(char* attr, char* newValue);
void stockManagementGet(int index, char* out, int lengthOut, char* data){
   int i = 0;
   char *row = strtok(data, "\n");
   for (i = 1; i < index; i++){
       row = strtok(NULL, "\n");
   }
   out = row;
}
