FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    make \
    git

WORKDIR /home/sockets_cpp/

# RUN git clone https://github.com/john9francis/sockets_cpp.git

COPY . /home/sockets_cpp/

# WORKDIR /home/sockets_cpp/sockets_cpp/

RUN make linux

CMD [ "./lin/server" ]