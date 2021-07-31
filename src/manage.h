#ifndef C_STOCK_MANAGER_MANAGE_HEADER
#define C_STOCK_MANAGER_MANAGE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void stockManagementUpdate(int, char*, char*);
void stockManagementDelete(int);
void stockManagementSet(char*, FILE*);
void stockManagementGet(char*, char*, int, char*, int);

#endif
