#ifndef C_STOCK_MANAGER_MANAGE_HEADER
#define C_STOCK_MANAGER_MANAGE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void stockManagementTrade(int opt, int quantity, char* productIndex, char* pathToRegister, char* pathToStockFile, char* data, int sizeOfData);
void stockManagementRead(char* pathToStockFile, char** data, unsigned long long* lengthOfData, unsigned long long* sizeOfData);
void stockManagementUpdate(char* productIndex, char* attribute, char* newValue, char* allAttributes, char* data, char* pathToStockFile);
void stockManagementDelete(char* productIndex, char* data, char* pathToStockFile);
void stockManagementSet(char* newValue, FILE* writePointer);
void stockManagementGet(char* index, char* out, unsigned long lengthOut, char* data, int sizeOfData);

#endif
