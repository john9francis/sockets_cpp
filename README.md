# sockets_cpp

6/29/2024 IT WORKS!

A simple communication over the network using sockets in C++. For this project, I will create a server that listens for connections. Then the server can periodically send the client information and the client will send back a message saying if it received the message or not.

# Development Environment
This project was developed on a windows machine. The Dockerfile and .devcontainer allow me to create a linux environment for testing if this works on linux. Also zig allows me to cross compile for linux on my windows machine.

zig version: 0.11.0

# Docker build process:
```
# docker rm sockets_dev_con 
docker build -t sockets_dev_img .
docker run -d --name sockets_dev_con sockets_dev_img
```
then go into the devcontainers menu and "attach to running container" and choose sockets_dev_con.

Then I can edit the code from my linux window or my windows window.

# Testing the server with docker
```
docker build -t sockets_dev_img .
docker run -d -p 8080:8080 --name test_server sockets_dev_img
# note: that is <host port>:<container port>
```
Then run .\win\client or ./lin/client from local machine, and the linux server will answer!

# Available ports:
source: chatGPT

**Well-known Ports (0-1023):** These are reserved for well-known services and protocols (e.g., HTTP on port 80, HTTPS on port 443, FTP on port 21). They require superuser (root) privileges to bind on Unix-like systems.

**Registered Ports (1024-49151):** These are assigned by the Internet Assigned Numbers Authority (IANA) for specific services. However, they can also be used by ordinary user applications.

**Dynamic or Private Ports (49152-65535):** These are not assigned to any specific service and are typically used for client-side communications or ephemeral ports, which are short-lived and used for temporary communications.

# TODO:
- [x] Got the server and client sending messages to eachother (on linux so far)
- [x] Get them sending strings to eachother and decoding them properly
- [x] Figure out how to un-cache the dockerfile command 'git clone...' (my solution is COPY)
- [x] Make my own cross platform header file
- [ ] Allow a port to be passed as an argv
- [ ] Allow port to be checked for availability during runtime
- [ ] Add more runtime error checking so it's as robust as possible
- [ ] Implement this server and client for my own use case.
- [ ] Make video showcasing the differences

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