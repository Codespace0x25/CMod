# Define variables
CC := $(shell command -v modcc 2>/dev/null || echo gcc)
CFLAGS = -Wall -Wextra -g -fPIC -I./include 
LDFLAGS = -shared
LIB_DIR = ./build
INCLUDE_DIR = ./include
SRC_DIR = ./src
LIB_NAME = libcmod.so
OUTPUT_DIR = ./bin
EXEC_NAME = myprogram

# Create directories
$(shell mkdir -p $(LIB_DIR) $(OUTPUT_DIR))

# ============================ LIBRARY BUILD =============================
# Compile all .c files into .o files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(LIB_DIR)/%.o)

# Rule to build .o files from .c files with position-independent code (PIC)
$(LIB_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Target for building the shared library
$(LIB_DIR)/$(LIB_NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# ============================ EXECUTABLE BUILD ===========================
# Rule for building the executable, dynamically linking the shared library
$(OUTPUT_DIR)/$(EXEC_NAME): $(SRC_DIR)/main.c $(LIB_DIR)/$(LIB_NAME)
	$(CC) $(CFLAGS) -L$(LIB_DIR) -Wl,-rpath,$(LIB_DIR) -lcmod -o $@ $<

# ============================ CLEANING ============================
.PHONY: clean
clean:
	rm -rf $(LIB_DIR)/*.o $(LIB_DIR)/$(LIB_NAME) $(OUTPUT_DIR)/*

# ============================ REMOVE LIBRARY ============================
.PHONY: remove-lib
remove-lib:
	rm -f /usr/lib/$(LIB_NAME) /usr/include/cmod.h
	rm -f /usr/bin/modcc /usr/bin/modrun

# ============================ INSTALLATION ============================
.PHONY: install
install: modrun modcc $(LIB_DIR)/$(LIB_NAME)
	cp $(LIB_DIR)/$(LIB_NAME) /usr/lib/
	cp $(INCLUDE_DIR)/cmod.h /usr/include/
	cp ./scripts/modcc /usr/bin/
	cp ./scripts/modrun /usr/bin/

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
	LD_LIBRARY_PATH=$(LIB_DIR) $(OUTPUT_DIR)/$(EXEC_NAME)
