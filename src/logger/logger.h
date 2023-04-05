#ifndef LOGGER_H
#define LOGGER_H

enum {
    LOG_LEVEL_ALL,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_NONE
};

void logInit(int level);
void logClose(void);
void logMessage(int level, const char* message, ...);

#endif
