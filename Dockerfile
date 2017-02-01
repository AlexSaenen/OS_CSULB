FROM alpine:3.5

RUN apk add --no-cache gcc g++ musl-dev valgrind bash git make
