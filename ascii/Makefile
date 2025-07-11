CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Wno-strict-prototypes -g -Iinclude
LDFLAGS = -lncurses

SRC = $(wildcard src/*.c src/layers/*.c)
OBJ = $(SRC:.c=.o)

TARGET = ascii

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./$(TARGET)
