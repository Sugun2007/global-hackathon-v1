# Makefile for C Data Structures Library (c-ds-lib)

# Compiler and tools
CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic -Iinclude
AR      = ar
RANLIB  = ranlib

# Directories
SRC_DIR      = src
INCLUDE_DIR  = include
TESTS_DIR    = tests
BUILD_DIR    = build

# Source files
SOURCES  = $(wildcard $(SRC_DIR)/*.c)
OBJECTS  = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADERS  = $(wildcard $(INCLUDE_DIR)/*.h)

# Libraries
STATIC_LIB = libds.a
SHARED_LIB = libds.so

# Installation directories
INSTALL_LIB_DIR     = /usr/local/lib
INSTALL_INCLUDE_DIR = /usr/local/include/ds

# Default target
all: $(STATIC_LIB)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library
$(STATIC_LIB): $(OBJECTS)
	$(AR) rcs $@ $^
	$(RANLIB) $@
	@echo "Static library $(STATIC_LIB) created successfully"

# Create shared library (optional)
$(SHARED_LIB): $(OBJECTS)
	$(CC) -shared -fPIC $(OBJECTS) -o $@
	@echo "Shared library $(SHARED_LIB) created successfully"

# Build both static and shared libraries
both: $(STATIC_LIB) $(SHARED_LIB)
	@echo "Both libraries built successfully"

# Demo target
demo: $(STATIC_LIB)
	$(CC) $(CFLAGS) $(SRC_DIR)/demo.c -L. -lds -o demo
	@echo "Demo executable 'demo' created successfully"

# Test target
test: $(STATIC_LIB)
	@if [ -d "$(TESTS_DIR)" ] && [ -n "$(wildcard $(TESTS_DIR)/*.c)" ]; then \
		for test_file in $(TESTS_DIR)/*.c; do \
			test_name=$$(basename $$test_file .c); \
			echo "Compiling test: $$test_name"; \
			$(CC) $(CFLAGS) $$test_file -L. -lds -o $(BUILD_DIR)/$$test_name; \
		done; \
		echo "Running tests."; \
		for test_exe in $(BUILD_DIR)/test_*; do \
			if [ -f "$$test_exe" ] && [ -x "$$test_exe" ]; then \
				echo "Running $$(basename $$test_exe)."; \
				./$$test_exe; \
			fi; \
		done; \
	else \
		echo "No test files found in $(TESTS_DIR)/"; \
	fi

# Install static library and headers
install: $(STATIC_LIB)
	@echo "Installing library and headers."
	# Create installation directories
	sudo mkdir -p $(INSTALL_LIB_DIR)
	sudo mkdir -p $(INSTALL_INCLUDE_DIR)
	# Install static library
	sudo cp $(STATIC_LIB) $(INSTALL_LIB_DIR)/
	# Install shared library if it exists
	@if [ -f "$(SHARED_LIB)" ]; then \
		sudo cp $(SHARED_LIB) $(INSTALL_LIB_DIR)/; \
		echo "Shared library $(SHARED_LIB) installed"; \
	fi
	# Install headers
	for header in $(HEADERS); do \
		sudo cp $$header $(INSTALL_INCLUDE_DIR)/; \
	done
	# Update library cache
	sudo ldconfig
	@echo "Installation completed successfully"
	@echo "Headers installed in: $(INSTALL_INCLUDE_DIR)/"
	@echo "Libraries installed in: $(INSTALL_LIB_DIR)/"
	@echo "You can now compile with: gcc main.c -lds"

# Uninstall libraries and headers
uninstall:
	@echo "Uninstalling library and headers."
	sudo rm -f $(INSTALL_LIB_DIR)/$(STATIC_LIB)
	sudo rm -f $(INSTALL_LIB_DIR)/$(SHARED_LIB)
	sudo rm -rf $(INSTALL_INCLUDE_DIR)
	sudo ldconfig
	@echo "Uninstallation completed successfully"

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(STATIC_LIB) $(SHARED_LIB)
	rm -f demo
	@echo "Clean completed successfully"

# Show help
help:
	@echo "Available targets:"
	@echo "  all        - Build static library (default)"
	@echo "  both       - Build both static and shared libraries"
	@echo "  demo       - Build demo executable"
	@echo "  test       - Compile and run tests"
	@echo "  install    - Install library and headers system-wide"
	@echo "  uninstall  - Remove installed library and headers"
	@echo "  clean      - Remove all build artifacts"
	@echo "  help       - Show this help message"

.PHONY: all both demo test install uninstall clean help
