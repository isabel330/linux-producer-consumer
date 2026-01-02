#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include "buffer.h"
#include "producer.h"
#include "consumer.h"
#include "watchdog.h"
#include <unistd.h>   // sleep
#include <time.h>    //time

buffer_t buffer;

volatile int running = 1;

int watchdog_interval = 0;
time_t last_consume_time;

void handle_sigint(int sig) {
    running = 0;  
}

int main() {
    pthread_t prod, cons;
    pthread_t wd;

    buffer_init(&buffer);

    watchdog_interval = 5; 
    last_consume_time = time(NULL);
 
    signal(SIGINT, handle_sigint);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_create(&wd, NULL, watchdog, NULL);

    while (running) {
        sleep(1);
    }

    // Graceful shutdown
    pthread_mutex_lock(&buffer.mutex);
    pthread_cond_broadcast(&buffer.not_empty);
    pthread_cond_broadcast(&buffer.not_full);
    pthread_mutex_unlock(&buffer.mutex);


    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    pthread_join(wd, NULL);

    printf("Program exited gracefully.\n");
    return 0;
}
