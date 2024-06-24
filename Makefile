
linux:
	zig c++ --target=x86_64-linux main.cc -o lin/main

windows:
	zig c++ main.cc -o win/main.exe

.PHONY: windows linux