#ifndef APP_UTILITIES_LOGGER_H
#define APP_UTILITIES_LOGGER_H

#include <stdio.h>
#include <time.h>
#include <string.h>

extern FILE* log_file;
extern char file_name[45];

#define LOG_FILE_CREATE() \
{ \
    time_t current_time = time(NULL); \
    struct tm* localTime = localtime(&current_time); \
    char timestamp[20]; \
    strftime(timestamp, sizeof(timestamp), "%Y%m%d-%H%M%S", localTime);\
    strcat(file_name, timestamp); \
    strcat(file_name, ".log.gz"); \
    log_file = fopen(file_name, "a");\
    if(log_file == NULL) \
    { \
        printf("Could not create a log file. Will display logs during runtime.\n"); \
    } \
    else \
    { \
        printf("Created log file %s\n", file_name); \
        fclose(log_file); \
      \
    } \
}

#define LOG_FILE_OPEN() \
{\
    log_file = fopen(file_name, "a");\
    if(log_file == NULL) \
    { \
        printf("Could not create a log file. Will display logs during runtime.\n"); \
    } \
}

#define LOG_FILE_CLOSE() \
{ \
    if(log_file != NULL) \
    { \
        fclose(log_file);\
    }; \
}

#define LOG_FILE_PROGRAM_END()\
{ \
    LOG("Exit Sufier.");\
}

/**
 * @brief Display MESSAGE with time format year:month:day-hour-minute-second
 * @param MESSAGE user provided text
 * @return void
 */
#define LOG(...) \
{ \
    time_t current_time = time(NULL); \
    struct tm* localTime = localtime(&current_time); \
    char timestamp[20]; \
    strftime(timestamp, sizeof(timestamp), "%Y:%m:%d-%H:%M:%S", localTime);\
    LOG_FILE_OPEN(); \
    if(log_file == NULL) \
    { \
        printf("%s: %s:%d - ", timestamp, __FILE__, __LINE__);\
        printf(__VA_ARGS__); \
        printf("\n"); \
    } \
    else\
    { \
        fprintf(log_file, "%s: %s:%d - ", timestamp, __FILE__, __LINE__); \
        fprintf(log_file, __VA_ARGS__); \
        fprintf(log_file, "\n"); \
    } \
    LOG_FILE_CLOSE(); \
}

#endif // APP_UTILITIES_LOGGER_H