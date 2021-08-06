#ifndef C_STOCK_MANAGER_MANAGE_HEADER
#define C_STOCK_MANAGER_MANAGE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void stockManagementTrade(int, int, char*);
void stockManagementRead(char*, char**, unsigned long long*, unsigned long long*);
void stockManagementUpdate(char*, char*, char*, char*, char*, char*);
void stockManagementDelete(char*, char*, char*);
void stockManagementSet(char*, FILE*);
void stockManagementGet(char*, char*, unsigned long, char*, int);

#endif
