#include "buffer.h"

void buffer_init(buffer_t *buf)
{
    buf->head = 0;
    buf->tail = 0;
    buf->count = 0;

    pthread_mutex_init(&buf->mutex, NULL);
    pthread_cond_init(&buf->not_full, NULL);
    pthread_cond_init(&buf->not_empty, NULL);
}

void buffer_put(buffer_t *buf, int value)
{
    pthread_mutex_lock(&buf->mutex);

    while (buf->count == BUFFER_SIZE)
        pthread_cond_wait(&buf->not_full, &buf->mutex);

    buf->data[buf->tail] = value;
    buf->tail = (buf->tail + 1) % BUFFER_SIZE;
    buf->count++;

    pthread_cond_signal(&buf->not_empty);
    pthread_mutex_unlock(&buf->mutex);
}

int buffer_get(buffer_t *buf)
{
    pthread_mutex_lock(&buf->mutex);

    while (buf->count == 0)
        pthread_cond_wait(&buf->not_empty, &buf->mutex);

    int value = buf->data[buf->head];
    buf->head = (buf->head + 1) % BUFFER_SIZE;
    buf->count--;

    pthread_cond_signal(&buf->not_full);
    pthread_mutex_unlock(&buf->mutex);

    return value;
}
