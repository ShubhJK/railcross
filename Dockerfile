FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    libssl-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir -p build

RUN g++ -std=c++17 -O2 -Wall -Wextra -DCPPHTTPLIB_OPENSSL_SUPPORT -Icpp/include -Icpp/third_party \
    cpp/server/server_main.cpp cpp/server/Server.cpp cpp/src/DataStore.cpp \
    -o build/railcross_server -lssl -lcrypto -lpthread

EXPOSE 8080

CMD ["./build/railcross_server"]
