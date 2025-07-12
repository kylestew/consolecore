CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Wno-strict-prototypes -g -Iinclude -I/opt/homebrew/opt/sdl2/include
LDFLAGS = -L/opt/homebrew/opt/sdl2/lib -lSDL2 -lm

SRC = $(wildcard src/*.c src/layers/*.c)
# OBJ = $(SRC:.c=.o)

TARGET = aether

build:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# all: $(TARGET)
#
# $(TARGET): $(OBJ)
# 	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
#
# %.o: %.c 
# 	$(CC) $(CFLAGS) -c $< -o $@
#
clean:
	rm -f $(TARGET) 
	rm -rf *.dSYM

run:
	./$(TARGET)
