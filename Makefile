SRC_DIR = src
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.cc)

all:
	@echo please specify 'windows' or 'linux'

windows: wserver wclient

linux: server client

# linux:
# 	zig c++ --target=x86_64-linux main.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/main

# windows:
# 	zig c++ --target=x86_64-windows main.cc $(SOURCES) -I$(INCLUDE_DIR) -o win/main.exe

.PHONY: windows linux all server client wserver wclient

# ===============================================================

server:
	g++ server.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/server

client:
	g++ client.cc $(SOURCES) -I$(INCLUDE_DIR) -o lin/client

wserver:
	g++ server.cc $(SOURCES) -I$(INCLUDE_DIR) -o win/server -lws2_32

wclient:
	g++ client.cc $(SOURCES) -I$(INCLUDE_DIR) -o win/client -lws2_32