SRC_DIR = src
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.cc)

all: linux windows

linux:
	zig c++ --target=x86_64-linux main.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/main

windows:
	zig c++ --target=x86_64-windows main.cc $(SOURCES) -I$(INCLUDE_DIR) -o win/main.exe

.PHONY: windows linux all gnulinux


gnulinux:
	g++ main.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/main