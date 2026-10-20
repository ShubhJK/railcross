// RoutePlanner.h — Planning engine
#pragma once
#include "Crossing.h"
#include "Route.h"
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <algorithm>

struct City {
    std::string name;
    double lat;
    double lng;
};

class RoutePlanner {
private:
    std::vector<std::shared_ptr<Crossing>> crossings;
    std::vector<City> cities;

    static constexpr double PI = 3.14159265358979323846;

    double haversine(const City& a, const City& b) const {
        const double R = 6371.0;
        const double dLat = (b.lat - a.lat) * PI / 180.0;
        const double dLng = (b.lng - a.lng) * PI / 180.0;
        const double lat1 = a.lat * PI / 180.0;
        const double lat2 = b.lat * PI / 180.0;
        const double h = std::sin(dLat/2)*std::sin(dLat/2) +
                         std::cos(lat1)*std::cos(lat2)*
                         std::sin(dLng/2)*std::sin(dLng/2);
        return 2.0 * R * std::asin(std::sqrt(h));
    }

    std::shared_ptr<Crossing> findCrossingForCity(const std::string& city) const {
        for (const auto& c : crossings)
            if (c->getCity() == city) return c;
        return nullptr;
    }

    const City* findCity(const std::string& name) const {
        for (const auto& c : cities)
            if (c.name == name) return &c;
        return nullptr;
    }

public:
    RoutePlanner(std::vector<std::shared_ptr<Crossing>> cs, std::vector<City> ct)
        : crossings(std::move(cs)), cities(std::move(ct)) {}

    std::vector<Route> plan(const std::string& fromName,
                            const std::string& toName) const {
        std::vector<Route> routes;
        const City* from = findCity(fromName);
        const City* to   = findCity(toName);
        if (!from || !to || fromName == toName) return routes;

        const double straightKm = haversine(*from, *to);
        const double roadKm     = std::max(12.0, straightKm * 1.24);
        const double baseMin    = (roadKm / 55.0) * 60.0;

        auto originX = findCrossingForCity(fromName);
        auto destX   = findCrossingForCity(toName);

        Route r1("Main Highway Corridor", "Most direct",
                 roadKm * 1.00, baseMin * 1.00);
        if (originX) r1.addCrossing(originX);
        routes.push_back(r1);

        Route r2("Ring Road Bypass", "Zero crossings",
                 roadKm * 1.17, baseMin * 1.17);
        routes.push_back(r2);

        Route r3("City Shortcut", "Shortest distance",
                 roadKm * 0.93, baseMin * 0.93);
        if (originX) r3.addCrossing(originX);
        if (destX && destX != originX) r3.addCrossing(destX);
        routes.push_back(r3);

        return routes;
    }
};