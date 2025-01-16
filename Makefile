CC = gcc
CFLAGS = -Wall
TARGET = bin/main
SOURCES = src/main.c src/conn.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)