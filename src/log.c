#include "log.h"

#ifndef LOG_FILE_PATH
#define LOG_FILE_PATH ""
#endif

void csmLog(char *toWrite, char* desc, char* file, int line) {
    FILE *logWriter = fopen(LOG_FILE_PATH, "a");
    if (logWriter == NULL) {
        fprintf(stderr, "Could not find log file\n");
        exit(1);
    }
    time_t time_now = time(NULL);
    struct tm loc_time = *localtime(&time_now);
    fprintf(logWriter, "[DEBUG] %d/%d/%d %d:%d:%d\nFILE: %s\nLINE: %d\n", loc_time.tm_mday, loc_time.tm_mon + 1, loc_time.tm_year + 1900, loc_time.tm_hour, loc_time.tm_min, loc_time.tm_sec, file, line);
    if (desc != NULL) {
        fputs(desc, logWriter);
        fputs("\n", logWriter);
    }

    fputs(toWrite, logWriter);
    fclose(logWriter);
}
