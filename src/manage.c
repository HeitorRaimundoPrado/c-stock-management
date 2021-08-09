#include "manage.h"
#include "log.h"

#ifndef C_STOCK_MANAGER_BUILD_TYPE
#define C_STOCK_MANAGER_BUILD_TYPE "Release"
#endif

void stockManagementPrintRow(char* row, char* attributes) {
    char attrToPrint[100], rowToPrint[100];
    char attrCopy[100];
    strcpy(attrCopy, attributes);

    char rowCopy[100];
    strcpy(rowCopy, row);

    char *tok = strtok(attrCopy, ",");

    unsigned long max_len = 0;
    while (tok != NULL) {
        if (strlen(tok) > max_len) {
            max_len = strlen(tok);
        }
        tok = strtok(NULL, ",");
    }

    tok = strtok(rowCopy, ",");
    while (tok != NULL) {
        if (strlen(tok) > max_len) {
            max_len = strlen(tok);
        }
        tok = strtok(NULL, ",");
    }

    sprintf(attrToPrint, "%%%lus", max_len+3);
    sprintf(rowToPrint, "%%%lus", max_len+3);
    
    if(strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0) {
        csmLog(attrToPrint, "FORMATTING STRING TO PRINT (ATTRIBUTES)", __FILE__, __LINE__);
        csmLog(rowToPrint, "FORMATTING STRING TO PRINT (ROW)", __FILE__, __LINE__);
    }

    strcpy(attrCopy, attributes);
    strcpy(rowCopy, row);

    printf("\n");
    tok = strtok(attrCopy, ",");
    while(tok != NULL) {
        printf(attrToPrint, tok);
        tok = strtok(NULL, ",");
    }
    printf("\n");

    tok = strtok(rowCopy, ",");
    while(tok != NULL) {
        printf(rowToPrint, tok);
        tok = strtok(NULL, ",");
    }
    printf("\n");
}

void stockManagementTrade(int opt, int quantity, char* productIndex, char* pathToRegister, char* pathToStockFile, char* data, int sizeOfData) {
    enum tradeOptions {sale=1, purchase};
    char row[100];
    char *dataCopy = malloc(strlen(data)*sizeof(char));
    if (dataCopy == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    strcpy(dataCopy, data);
    stockManagementGet(productIndex, row, 100, data, sizeOfData);

    char *allAttr = strtok(dataCopy, "\n");
    char allAttrCopy[100];
    strcpy(allAttrCopy, allAttr);

    char *attr = strtok(allAttr, ",");
    int indexOfQuantity, indexOfPrice, i = 0;
    long int TotalQuantity = 0;
    double price;
    while (attr != NULL) {
        if (strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0){
            csmLog(attr, "attr", __FILE__, __LINE__);
        }

        if(strcmp(attr, "Quantity") == 0) {
            indexOfQuantity = i;
        }
        else if(strcmp(attr, "Price") == 0) {
            indexOfPrice = i;
        }
        attr = strtok(NULL, ",");
        i++;
    }
    if (strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0) {
        char iAsStr[30];
        sprintf(iAsStr, "%d", indexOfPrice);
        csmLog(iAsStr, "indexOfPrice:", __FILE__, __LINE__);
        sprintf(iAsStr, "%d", indexOfQuantity);
        csmLog(iAsStr, "indexOfQuantity:", __FILE__, __LINE__);
    }

    char *val = strtok(row, ",");
    i = 0;
    while(val != NULL) {
        if(strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0) {
            csmLog(val, "VAl", __FILE__, __LINE__);
        }
        if (i == indexOfPrice) {
            if (strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0) {
                csmLog(val, "VAL FOR PRICE", __FILE__, __LINE__);
            }

            char *p;
            price = strtod(val, &p);
            if (*p != 0) {
                fprintf(stderr, "Price field of product of index %s is not a number\n", productIndex);
            }

        }
        else if (i == indexOfQuantity) {
            if(strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0) {
                csmLog(val, "VAL FOR TotalQuantity", __FILE__, __LINE__);
            }

            char *p;
            TotalQuantity = strtol(val, &p, 10);

            if (*p != 0) {
                fprintf(stderr, "Quantity field of product of index %s is not number\n", productIndex);
            }

        }
        val = strtok(NULL, ",");
        i++;
    }

    if (strcmp(C_STOCK_MANAGER_BUILD_TYPE, "Debug") == 0) {
        char totQuantAsStr[30];
        sprintf(totQuantAsStr, "%ld", TotalQuantity);
        csmLog(totQuantAsStr, "TOTAL QUANTITY OF ITEM:", __FILE__, __LINE__);
        sprintf(totQuantAsStr, "%d", quantity);
        csmLog(totQuantAsStr, "QUANTITY SOLD OF ITEM:", __FILE__, __LINE__);
    }

    if (opt == sale) {
       FILE *registerWriter = fopen(pathToRegister, "a"); 
       if (registerWriter == NULL) {
           fprintf(stderr, "Unable to open file: %s", pathToRegister);
           exit(1);
       }

       char toWrite[150];
       sprintf(toWrite, "Sale,%s,%d,%.2lf,%.2lf,\n", productIndex,quantity, price, price*quantity);

       fputs(toWrite, registerWriter);

       fclose(registerWriter);

       char newQuantAsStr[30];
       sprintf(newQuantAsStr, "%ld", TotalQuantity-quantity);

       stockManagementUpdate(productIndex, "Quantity", newQuantAsStr, allAttrCopy, data, pathToStockFile);
    }
    else {
        FILE *registerWriter = fopen(pathToRegister, "a");
        if (registerWriter == NULL) {
            fprintf(stderr, "Unable to open file: %s", pathToRegister);
            exit(1);
        }
        char toWrite[150];
        sprintf(toWrite, "Purchase,%s,%d,%.2lf,%.2lf\n", productIndex, quantity, price, quantity*price);
        fputs(toWrite, registerWriter);

        fclose(registerWriter);

        char newQuantAsStr[30];
        sprintf(newQuantAsStr, "%ld", TotalQuantity+quantity);

        stockManagementUpdate(productIndex, "Quantity", newQuantAsStr, allAttrCopy, data, pathToStockFile);
    }

    free(dataCopy);
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
       if (strlen(productIndex) == strcspn(row, ",") && strncmp(productIndex, row, strcspn(row, ",")) == 0){
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
       if (strlen(index) == strcspn(row, ",") && strncmp(index, row, strcspn(row, ",")) == 0){ 
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
