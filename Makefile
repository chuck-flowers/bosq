# Application Settings
BIN_NAME=bosq

# Installation Settings
PREFIX ?= /usr/local

# Compiler Settings
CC=gcc
CFLAGS += -c -Wall -Wpedantic -Werror
LFLAGS +=

# Pandoc Settings
PANDOC ?= pandoc
PANDOC_FLAGS ?= --standalone

# Project Directories
SRC_DIR ?= src
DST_DIR ?= build

.PHONY: all install uninstall clean
all: bin man
install: install-bin install-man
uninstall: uninstall-bin uninstall-man
clean:
	-rm -rf $(DST_DIR)
	-rm $(wildcard $(SRC_DIR)/*.o)

# Source Files
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
INC_FILES=$(wildcard $(SRC_DIR)/*.h)

# Build Files
OBJ_FILES=$(patsubst %.c, %.o, $(SRC_FILES))
DST_BIN_FILE=$(DST_DIR)/bin/$(BIN_NAME)

.PHONY: bin install-bin uninstall-bin
bin: $(DST_BIN_FILE)
$(DST_BIN_FILE): $(OBJ_FILES)
	mkdir -p $(dir $(DST_BIN_FILE))
	$(CC) $(LFLAGS) $^ -o $@
%.o: %.c %.h
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
install-bin:
	mkdir -p $(PREFIX)/bin
	install -t $(PREFIX)/bin $(DST_BIN_FILE)
uninstall-bin:
	-rm $(PREFIX)/bin/$(BIN_NAME)

# Man Pages
SRC_MAN_DIR=$(SRC_DIR)/man
DST_MAN_DIR=$(DST_DIR)/man
SRC_MAN_MD_FILES=$(shell find $(SRC_MAN_DIR) -type f -name '*.md')
DST_MAN_PAGES=$(patsubst $(SRC_MAN_DIR)/%.md, $(DST_MAN_DIR)/%, $(SRC_MAN_MD_FILES))

.PHONY: man install-man
man: $(DST_MAN_PAGES)
$(DST_MAN_DIR)/%: $(SRC_MAN_DIR)/%.md 
	mkdir -p $(dir $@)
	$(PANDOC) $(PANDOC_FLAGS) $< --to man -o $@
install-man:
	$(foreach p,$(patsubst $(DST_MAN_DIR)/%,$(PREFIX)/share/man/%,$(DST_MAN_PAGES)),mkdir -p $(dir $(p)))
	$(foreach p,$(DST_MAN_PAGES),install -t $(patsubst $(DST_MAN_DIR)/%,$(PREFIX)/share/man/%,$(dir $(p))) $(p))
uninstall-man:
	-rm $(patsubst $(DST_MAN_DIR)/%, $(PREFIX)/share/man/%, $(page))

# Development
.PHONY: dev
dev: clean
	bear -- make

