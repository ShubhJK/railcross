// JsonSerializer.h — Crossing / Route to JSON
#pragma once
#include "Crossing.h"
#include "Route.h"
#include "RoutePlanner.h"
#include "json.hpp"
#include <memory>

using json = nlohmann::json;

namespace RailJson {

    inline json crossingToJson(const std::shared_ptr<Crossing>& c) {
        return json{
            { "id",             c->getId() },
            { "name",           c->getName() },
            { "city",           c->getCity() },
            { "state",          c->getState() },
            { "zone",           c->getZone() },
            { "division",       c->getDivision() },
            { "line",           c->getLine() },
            { "landmark",       c->getLandmark() },
            { "alternateRoute", c->getAlternateRoute() },
            { "avgWaitMinutes", c->getAvgWaitMinutes() },
            { "dailyTrains",    c->getDailyTrains() },
            { "latitude",       c->getLatitude() },
            { "longitude",      c->getLongitude() },
            { "status",         c->statusString() },
            { "expectedWait",   c->expectedWaitSeconds() },
            { "secondsToNext",  c->getSecondsToNext() }
        };
    }

    inline json crossingsToJson(const std::vector<std::shared_ptr<Crossing>>& cs) {
        json arr = json::array();
        for (const auto& c : cs) arr.push_back(crossingToJson(c));
        return json{ { "crossings", arr }, { "count", arr.size() } };
    }

    inline json citiesToJson(const std::vector<City>& cities) {
        json arr = json::array();
        for (const auto& c : cities)
            arr.push_back({ { "name", c.name }, { "lat", c.lat }, { "lng", c.lng } });
        return json{ { "cities", arr }, { "count", arr.size() } };
    }

    inline json routeToJson(const Route& r) {
        json crossings = json::array();
        for (const auto& c : r.getCrossings()) {
            crossings.push_back({
                { "id",           c->getId() },
                { "name",         c->getName() },
                { "landmark",     c->getLandmark() },
                { "status",       c->statusString() },
                { "expectedWait", c->expectedWaitSeconds() }
            });
        }
        return json{
            { "name",         r.getName() },
            { "tag",          r.getTag() },
            { "distanceKm",   r.getDistanceKm() },
            { "baseMinutes",  r.getBaseMinutes() },
            { "crossingDelay",r.crossingDelayMinutes() },
            { "totalMinutes", r.totalMinutes() },
            { "riskCount",    r.riskCount() },
            { "crossings",    crossings }
        };
    }

    inline json routesToJson(const std::vector<Route>& routes) {
        json arr = json::array();
        for (const auto& r : routes) arr.push_back(routeToJson(r));
        return json{ { "routes", arr }, { "count", arr.size() } };
    }
}