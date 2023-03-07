# APPLICATION SETTINGS
BIN_NAME=bosq

# INSTALLATION SETTINGS
PREFIX ?= /usr/local

# TOOLS
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

# BINS
SRC_BIN_DIR=$(SRC_DIR)/bin
SRC_BIN_FILE=$(SRC_BIN_DIR)/$(BIN_NAME)
DST_BIN_DIR=$(DST_DIR)/bin
DST_BIN_FILE=$(DST_BIN_DIR)/$(BIN_NAME)
.PHONY: bin install-bin uninstall-bin
bin: $(DST_BIN_FILE)
install-bin:
	mkdir -p $(PREFIX)/bin
	install -m 755 $(DST_BIN_FILE) $(PREFIX)/bin/$(BIN_NAME)
uninstall-bin:
	-rm $(PREFIX)/bin/$(BIN_NAME)
$(DST_BIN_FILE): $(SRC_BIN_FILE)
	$(SHELLCHECK) $(SHELLCHECK_FLAGS) $^
	mkdir -p $(dir $@)
	install -m 755 $^ $@

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

