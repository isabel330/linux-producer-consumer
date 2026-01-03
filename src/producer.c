#include <stdio.h>
#include <unistd.h>
#include "producer.h"
#include "buffer.h"

void log_info(const char *fmt, ...);

extern volatile int running;
extern buffer_t buffer;
extern time_t last_consume_time;

void* producer(void* arg)
{
    int value = 0;

    while (running) {
        buffer_put(&buffer, value);
        log_info("Produced: %d", value);
        value++;
        sleep(1);
    }

    return NULL;
}
