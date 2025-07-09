# Detect Homebrew prefix
HOMEBREW_PREFIX := $(shell brew --prefix 2>/dev/null || echo /opt/homebrew)

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -I$(HOMEBREW_PREFIX)/include
LDFLAGS = -L$(HOMEBREW_PREFIX)/lib -lncurses -lportaudio -lm

# Source files
# SOURCES = main.c ui.c audio.c engine.c
SOURCES = main.c audio.c ui.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = obra

# Default target
all: dr_wav.h $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install dependencies (macOS)
install-deps:
	brew install portaudio ncurses
	@echo "Downloading dr_wav header file..."
	@if [ ! -f dr_wav.h ]; then \
		curl -o dr_wav.h https://raw.githubusercontent.com/mackron/dr_libs/master/dr_wav.h; \
		echo "✅ dr_wav.h downloaded successfully"; \
	else \
		echo "✅ dr_wav.h already exists"; \
	fi

# Run the program 
run: $(TARGET)
	./$(TARGET) 

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build the Obra music tracker"
	@echo "  clean            - Remove build artifacts"
	@echo "  install-deps     - Install dependencies (macOS)"
	@echo "  run              - Run with example samples"
	@echo ""
	@echo "Usage:"
	@echo "  ./obra"
	@echo ""

.PHONY: all clean install-deps run help 
