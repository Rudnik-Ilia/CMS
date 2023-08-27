FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y cmake g++ libboost-all-dev && \
    apt-get clean

RUN ls /usr/include/boost
RUN ls /usr/lib/x86_64-linux-gnu | grep boost

WORKDIR /app

COPY CMakeLists.txt /app/
COPY include /app/include
COPY src /app/src
COPY test /app/test

EXPOSE 9090
RUN apt-get update && apt-get install -y libboost-all-dev

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

CMD ["./build/your_program"]