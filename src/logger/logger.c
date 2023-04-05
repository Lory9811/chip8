#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static FILE* file;
static int logLevel = LOG_LEVEL_ALL;

void logInit(int level) {
    file = fopen("log.txt", "w");
    logLevel = level;
}

void logClose(void) {
    fclose(file);
}

void logMessage(int level, const char* message, ...) {
    if (logLevel > level) return;

    va_list args;
    va_start(args, message);
    vfprintf(file, message, args);
    va_end(args);
}
