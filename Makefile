# APPLICATION SETTINGS
BIN_NAME=bosq

# INSTALLATION SETTINGS
PREFIX ?= /usr/local

# TOOLS
CC=gcc
CFLAGS ?= -c -Wall -Wpedantic -Werror
LFLAGS ?=
PANDOC ?= pandoc
PANDOC_FLAGS ?= --standalone
SHELLCHECK ?= shellcheck
SHELLCHECK_FLAGS ?= --format tty

# PROJECT DIRS
SRC_DIR ?= src
DST_DIR ?= build

.PHONY: all install uninstall clean
all: bin man
install: install-bin install-man
uninstall: uninstall-man
clean:
	-rm -rf $(DST_DIR)
	-rm $(wildcard $(SRC_DIR)/*.o)

# BIN
.PHONY: bin install-bin uninstall-bin
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
INC_FILES=$(wildcard $(SRC_DIR)/*.h)
OBJ_FILES=$(patsubst %.c, %.o, $(SRC_FILES))
DST_BIN_FILE=$(DST_DIR)/bin/$(BIN_NAME)
bin: $(DST_BIN_FILE)
install-bin:
	install $(DST_BIN_FILE) $(PREFIX)/bin
$(DST_DIR)/bin/$(BIN_NAME): $(OBJ_FILES)
	mkdir -p $(dir $(DST_BIN_FILE))
	$(CC) $(LFLAGS) $^ -o $@
%.o: %.c %.h
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# MAN PAGES
SRC_MAN_DIR=$(SRC_DIR)/man
DST_MAN_DIR=$(DST_DIR)/man
SRC_MAN_MD_FILES=$(shell find $(SRC_MAN_DIR) -type f -name '*.md')
DST_MAN_PAGES=$(patsubst $(SRC_MAN_DIR)/%.md, $(DST_MAN_DIR)/%, $(SRC_MAN_MD_FILES))
.PHONY: man install-man
man: $(DST_MAN_PAGES)
install-man: $(patsubst $(DST_MAN_DIR)/%, $(PREFIX)/share/man/%, $(DST_MAN_PAGES))
$(PREFIX)/share/man/%:
	mkdir -p $(dir $@)
	install -m 444 $(patsubst $(PREFIX)/share/man/%, $(DST_MAN_DIR)/%, $@) $@
uninstall-man:
	-rm $(patsubst $(DST_MAN_DIR)/%, $(PREFIX)/share/man/%, $(page))
$(DST_MAN_DIR)/%: $(SRC_MAN_DIR)/%.md 
	mkdir -p $(dir $@)
	$(PANDOC) $(PANDOC_FLAGS) $< --to man -o $@

