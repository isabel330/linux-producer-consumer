#include <stdio.h>
#include <unistd.h>
#include "producer.h"
#include "buffer.h"

extern buffer_t buffer;

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
