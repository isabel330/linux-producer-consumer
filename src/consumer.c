#include <stdio.h>
#include <unistd.h>
#include "consumer.h"
#include "buffer.h"

void log_info(const char *fmt, ...);

extern buffer_t buffer;
extern time_t last_consume_time;
extern volatile int running;

void* consumer(void* arg)
{
    while (running) {
        int value = buffer_get(&buffer);
        log_info("Consumed: %d", value);
        last_consume_time = time(NULL);
        sleep(2);
    }

    return NULL;
}
