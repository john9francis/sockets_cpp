SRC_DIR = src
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.cc)

all: gnulinux

linux:
	zig c++ --target=x86_64-linux main.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/main

windows:
	zig c++ --target=x86_64-windows main.cc $(SOURCES) -I$(INCLUDE_DIR) -o win/main.exe

.PHONY: windows linux all gnulinux


gnulinux:
	g++ main.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/main
	./lin/main

server:
	g++ server.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/server

client:
	g++ client.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/client