#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>

#define BUFFER_SIZE 8

typedef struct {
    int data[BUFFER_SIZE];
    int head;
    int tail;
    int count;

    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} buffer_t;

void buffer_init(buffer_t *buf);
void buffer_put(buffer_t *buf, int value);
int  buffer_get(buffer_t *buf);

#endif
