// Server.h — RailCross HTTP server
#pragma once
#include "Crossing.h"
#include "RoutePlanner.h"
#include <vector>
#include <memory>
#include <string>

class RailServer {
public:
    RailServer(std::vector<std::shared_ptr<Crossing>> crossings,
               std::vector<City> cities,
               std::string webRoot,
               int port = 8080);
    void run();

private:
    std::vector<std::shared_ptr<Crossing>> crossings;
    std::vector<City> cities;
    std::string webRoot;
    int port;
};