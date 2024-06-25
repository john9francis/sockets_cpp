FROM alpine:latest

RUN apk add zig git make
# RUN apk add --no-cache musl-dev
RUN apk add --no-cache gcc g++

WORKDIR /home/sockets_cpp/

RUN git clone https://github.com/john9francis/sockets_cpp.git
