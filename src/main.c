#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h"

buffer_t buffer;

void* producer(void* arg)
{
    int value = 0;
    while (1) {
        buffer_put(&buffer, value);
        printf("Produced: %d\n", value++);
        sleep(1);
    }
}

void* consumer(void* arg)
{
    while (1) {
        int value = buffer_get(&buffer);
        printf("Consumed: %d\n", value);
        sleep(2);
    }
}

int main()
{
    pthread_t prod, cons;

    buffer_init(&buffer);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
