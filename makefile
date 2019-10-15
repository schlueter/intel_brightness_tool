.PHONY: test build install

CC = cc
FILES = brightness.c
OUT_EXE = brightness
INSTALL_DEST = /usr/local/bin
CURRENT_UID := $(shell id -u)

build: $(OUT_EXE)

$(OUT_EXE): $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)

test:

install:
	install --owner root --mode 04755 $(OUT_EXE) $(INSTALL_DEST)
