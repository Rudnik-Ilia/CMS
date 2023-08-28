FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y cmake g++ libboost-all-dev nlohmann-json3-dev && \
    apt-get clean

# RUN git clone https://github.com/nlohmann/json.git /app/include/nlohmann

WORKDIR /app

COPY src /app/src
COPY test /app/test
COPY include /app/include
COPY CMakeLists.txt /app

EXPOSE 9090

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

CMD ["./build/server"]

