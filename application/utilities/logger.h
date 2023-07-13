#ifndef APP_UTILITIES_LOGGER_H
#define APP_UTILITIES_LOGGER_H

#include <stdio.h>
#include <time.h>

/**
 * @brief Display MESSAGE with time format year:month:day-hour-minute-second
 * @param MESSAGE user provided text
 * @return void
 */
#define LOG(MESSAGE) \
{ \
    time_t current_time = time(NULL); \
    struct tm* localTime = localtime(&current_time); \
    char timestamp[20]; \
    strftime(timestamp, sizeof(timestamp), "%Y:%m:%d-%H:%M:%S", localTime);\
    printf("%s %s\n", timestamp, (MESSAGE));\
}


#endif // APP_UTILITIES_LOGGER_H