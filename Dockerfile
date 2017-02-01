FROM debian:jessie-slim

RUN apt-get update
RUN apt-get upgrade
RUN apt-get install -y gcc-4.9 g++-4.9 make valgrind
