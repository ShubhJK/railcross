// main.cpp — CLI demo driver
#include "DataStore.h"
#include "RoutePlanner.h"
#include "Route.h"
#include "Crossing.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <memory>

static void banner(const std::string& title) {
    std::cout << "\n" << std::string(66, '=') << "\n";
    std::cout << "  " << title << "\n";
    std::cout << std::string(66, '=') << "\n";
}

static void printAllCrossings(
    const std::vector<std::shared_ptr<Crossing>>& crossings) {
    banner("PUNJAB / PATIALA LEVEL CROSSINGS  -  LIVE STATUS");
    for (const auto& c : crossings) {
        std::cout << "  [" << c->getId() << "] " << c->getName() << "\n";
        std::cout << "      " << c->getLandmark() << ", " << c->getCity()
                  << "   |   " << c->getLine() << "\n";
        std::cout << "      Status: " << std::left << std::setw(8)
                  << c->statusString()
                  << " Expected wait: " << std::setw(4)
                  << c->expectedWaitSeconds() << "s"
                  << "   Trains/day: " << c->getDailyTrains() << "\n\n";
    }
}

int main() {
    auto crossings = DataStore::loadCrossings();
    auto cities    = DataStore::loadCities();

    printAllCrossings(crossings);

    RoutePlanner planner(crossings, cities);
    auto routes = planner.plan("Patiala", "Chandigarh");

    banner("ROUTE PLANNER  -  Patiala  ->  Chandigarh");
    std::cout << "  (before sorting)\n\n";
    for (const auto& r : routes) { std::cout << r << "\n"; }

    std::sort(routes.begin(), routes.end());

    banner("RANKED ROUTES  -  fastest first (operator<)");
    int rank = 1;
    for (const auto& r : routes) {
        std::cout << "  #" << rank++ << "\n";
        std::cout << r << "\n";
    }

    std::cout << "\n  Demo complete.\n\n";
    return 0;
}