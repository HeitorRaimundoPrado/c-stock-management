#ifndef C_STOCK_MANAGEMENT_SRC_LOG_H_HEADER
#define C_STOCK_MANAGEMENT_SRC_LOG_H_HEADER

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
 * Function to log toWrite to debug.log file automatically
 */
void csmLog(char *toWrite, char* desc, char* file, int line);

#endif
