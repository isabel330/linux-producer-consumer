#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>

static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

static void current_time(char* buffer, size_t len) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, len, "%Y-%m-%d %H:%M:%S", tm_info);
}

void log_info(const char* fmt, ...) {
    pthread_mutex_lock(&log_mutex);

    char timebuf[20];
    current_time(timebuf, sizeof(timebuf));
    printf("[%s] [INFO] ", timebuf);

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
    pthread_mutex_unlock(&log_mutex);
}

void log_error(const char* fmt, ...) {
    pthread_mutex_lock(&log_mutex);

    char timebuf[20];
    current_time(timebuf, sizeof(timebuf));
    fprintf(stderr, "[%s] [ERROR] ", timebuf);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "\n");
    pthread_mutex_unlock(&log_mutex);
}
