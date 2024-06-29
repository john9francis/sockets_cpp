# sockets_cpp
A simple communication over the network using sockets in C++. For this project, I will create a server that listens for connections. Then the server can periodically send the client information and the client will send back a message saying if it received the message or not.

# Development Environment
This project was developed on a windows machine. The Dockerfile and .devcontainer allow me to create a linux environment for testing if this works on linux. Also zig allows me to cross compile for linux on my windows machine.

zig version: 0.11.0

# Docker build process:
Sort of messy way to start up the container:
```
docker rm zig_dev_con 
docker build -t zig_dev_img .
docker run -i --name zig_dev_con zig_dev_img
# control c to end process
docker start zig_dev_con
```
then go into the devcontainers menu and "attach to running container" and choose zig_dev_con.

Then I can edit the code from my linux window or my windows window.


# TODO:
- [x] Got the server and client sending messages to eachother (on linux so far)
- [x] Get them sending strings to eachother and decoding them properly

# Dependencies
1. [Zig](https://ziglang.org/) (for cross compilation)
2. gcc and g++ for compilation in a devcontainer
3. [Make]() (optional: simply holds the build scripts, but they can be entered by hand.)

# Useful Websites
- [Zig platforms](https://ziglang.org/download/0.11.0/release-notes.html#Support-Table)
- [Install zig linux](https://github.com/ziglang/zig/wiki/Install-Zig-from-a-Package-Manager)
- [Detecting OS from C code](https://iq.opengenus.org/detect-operating-system-in-c/)
- [Beej's networking tutorial](https://beej.us/guide/bgnet/html/split/system-calls-or-bust.html#getaddrinfoprepare-to-launch)
- [Getting started with WinSock](https://learn.microsoft.com/en-us/windows/win32/winsock/initializing-winsock)