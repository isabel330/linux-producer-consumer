# Linux Producer–Consumer System (pthread)

A multithreaded producer–consumer system implemented in C on Linux using POSIX threads.  
The project demonstrates thread synchronization, condition variables, thread-safe logging, and watchdog supervision.

## Features
- Producer–consumer model with bounded buffer
- POSIX threads (`pthread`)
- Mutex + condition variable synchronization
- Thread-safe logger with timestamps
- Watchdog thread to detect stalled consumer
- Graceful shutdown support

## Build and run
```bash
gcc src/*.c -Iinclude -pthread -o app
./app
