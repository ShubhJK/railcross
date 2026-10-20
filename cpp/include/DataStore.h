// DataStore.h — Dataset loader
#pragma once
#include "Crossing.h"
#include "RoutePlanner.h"
#include <vector>
#include <memory>

class DataStore {
public:
    static std::vector<std::shared_ptr<Crossing>> loadCrossings();
    static std::vector<City>                      loadCities();
};