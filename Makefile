# Compiler and flags
CC = gcc
CFLAGS = -Wall -I./include

# Directories
SRCDIR = src
INCLUDEDIR = include
EXAMPLESDIR = examples
BINDIR = bin

# Source files
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRC))

# Example source files
EXAMPLES_SRC = $(wildcard $(EXAMPLESDIR)/*.c)
EXAMPLES_BIN = $(patsubst $(EXAMPLESDIR)/%.c, $(BINDIR)/%, $(EXAMPLES_SRC))

# Targets
all: $(OBJ) $(EXAMPLES_BIN)

# Build object files
$(BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build example binaries
$(BINDIR)/%: $(EXAMPLESDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(BINDIR)

# Default target
.DEFAULT_GOAL := all
