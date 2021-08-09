#ifndef C_STOCK_MANAGER_MANAGE_HEADER
#define C_STOCK_MANAGER_MANAGE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * Function to get the row of a specific product by index
 */
void stockManagementTrade(int opt, int quantity, char* productIndex, char* pathToRegister, char* pathToStockFile, char* data, int sizeOfData);

/*
 * Function to read the file that keeps track of current stock of products
 */
void stockManagementRead(char* pathToStockFile, char** data, unsigned long long* lengthOfData, unsigned long long* sizeOfData);

/*
 * Function to update the value of an attribute of an specific product passed by index
 */
void stockManagementUpdate(char* productIndex, char* attribute, char* newValue, char* allAttributes, char* data, char* pathToStockFile);

/*
 * Function to delete the row of a product on the file that keeps track of current stock
 */
void stockManagementDelete(char* productIndex, char* data, char* pathToStockFile);

/*
 * Function to set each attribute of a new row
 */
void stockManagementSet(char* newValue, FILE* writePointer);

/* 
 * Function to get the row of a product on the file that keeps track of stock
 */
void stockManagementGet(char* index, char* out, unsigned long lengthOut, char* data, int sizeOfData);

/*
 * Function to print the output of stockManagementGet
 */
void stockManagementPrintRow(char* row, char* attributes);

#endif
