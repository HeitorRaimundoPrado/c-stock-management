#ifndef C_STOCK_MANAGER_MANAGE_HEADER
#define C_STOCK_MANAGER_MANAGE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stockManagementUpdate(int, char*, char*);
void stockManagementDelete(int);
void stockManagementSet(char*, char*);
void stockManagementGet(int, char*, int, char*);

#endif
