
FROM ubuntu:latest

RUN apt-get update && apt-get install -y g++

COPY . /app/

WORKDIR /app
RUN apt install libboost-all-dev
RUN g++ -std=c++11 server.cpp -lpthread -o server

EXPOSE 9090

CMD ["./server"]
