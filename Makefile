CC = gcc
CFLAGS = -Wall -Wextra -pthread -Iinclude

SRC = src/main.c \
      src/buffer.c \
      src/producer.c \
      src/consumer.c

TARGET = app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
