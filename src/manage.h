#ifndef C_STOCK_MANAGER_MANAGE_HEADER
#define C_STOCK_MANAGER_MANAGE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void stockManagementTrade(int, int, int);
void stockManagementRead(char*, char**, unsigned long long*, unsigned long long*);
void stockManagementUpdate(int, char*, char*);
void stockManagementDelete(char*, unsigned long long, char*, char*);
void stockManagementSet(char*, FILE*);
void stockManagementGet(char*, char*, int, char*, int);

#endif
