FROM ubuntu:22.04

# Install build tools AND OpenSSL (required for your C++ backend to make HTTPS requests)
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

# Create the build directory BEFORE compiling
RUN mkdir -p build

# Compile with OpenSSL support
RUN g++ -std=c++17 -O2 -Wall -Wextra -DCPPHTTPLIB_OPENSSL_SUPPORT -Icpp/include -Icpp/third_party \
    cpp/server/server_main.cpp cpp/server/Server.cpp cpp/src/DataStore.cpp \
    -o build/railcross_server -lssl -lcrypto -lpthread

EXPOSE 8080

CMD ["./build/railcross_server"]
