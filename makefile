# Define variables
CC = gcc
CFLAGS = -Wall -Wextra -g -I./include
LIB_DIR = ./build
INCLUDE_DIR = ./include
SRC_DIR = ./src
LIB_NAME = libcmod.a
OUTPUT_DIR = ./bin
EXEC_NAME = myprogram

# Create directories
$(shell mkdir -p $(LIB_DIR) $(OUTPUT_DIR))

# ============================ LIBRARY BUILD =============================
# Compile all .c files into .o files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(LIB_DIR)/%.o)

# Rule to build .o files from .c files
$(LIB_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target for building the static library
$(LIB_DIR)/$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

# ============================ EXECUTABLE BUILD ===========================
# Rule for building the executable
$(OUTPUT_DIR)/$(EXEC_NAME): $(SRC_DIR)/main.c $(LIB_DIR)/$(LIB_NAME)
	$(CC) $(CFLAGS) -L$(LIB_DIR) -lprome -o $@ $^

# ============================ CLEANING ============================
.PHONY: clean
clean:
	rm -rf $(LIB_DIR)/*.o $(LIB_DIR)/$(LIB_NAME) $(OUTPUT_DIR)/*

# ============================ INSTALLATION ============================
.PHONY: install
install: modrun modcc $(LIB_DIR)/$(LIB_NAME)
	cp $(LIB_DIR)/$(LIB_NAME) /usr/local/lib/
	cp $(INCLUDE_DIR)/cmod.h /usr/local/include/
	cp ./scripts/modcc /usr/local/bin/
	cp ./scripts/modrun /usr/local/bin/

# ============================ CUSTOM COMMANDS ============================
# Custom compile command: modcc
modcc: scripts/modcc
	@echo "Running modcc script..."
	@chmod +x ./scripts/modcc

# Custom run command: modrun
modrun: scripts/modrun
	@echo "Running modrun script..."
	@chmod +x ./scripts/modrun

# ============================ BUILD THE LIBRARY ============================
all: $(LIB_DIR)/$(LIB_NAME)

# ============================ TESTING ============================
.PHONY: test
test: $(OUTPUT_DIR)/$(EXEC_NAME)
	$(OUTPUT_DIR)/$(EXEC_NAME)
