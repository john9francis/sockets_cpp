FROM alpine:latest

RUN apk add zig git make

WORKDIR /home/sockets_cpp/

RUN git clone https://github.com/john9francis/sockets_cpp.git
