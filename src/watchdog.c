#include <time.h>
#include <unistd.h>
#include "watchdog.h"

extern volatile int running;
extern time_t last_consume_time;
extern int watchdog_interval;

void* watchdog(void* arg)
{
    while (running) {
        sleep(watchdog_interval);

        time_t now = time(NULL);
        if (now - last_consume_time > watchdog_interval) {
            log_error("Watchdog: consumer stuck!");
        }
    }
    return NULL;
}
