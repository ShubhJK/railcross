// server_main.cpp — entry point for HTTP server
#include "Server.h"
#include "DataStore.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
    int port = 8080;
    if (argc > 1) port = std::atoi(argv[1]);

    std::string webRoot = "web";
    if (argc > 2) webRoot = argv[2];

    std::cout << "Loading Punjab / Patiala dataset...\n";
    auto crossings = DataStore::loadCrossings();
    auto cities    = DataStore::loadCities();
    std::cout << "  -> Loaded " << crossings.size() << " crossings\n";
    std::cout << "  -> Loaded " << cities.size()    << " cities\n";

    RailServer server(std::move(crossings), std::move(cities), webRoot, port);
    server.run();
    return 0;
}