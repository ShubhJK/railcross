// Route.h — Composition + operator overloading
#pragma once
#include "Crossing.h"
#include <vector>
#include <memory>
#include <ostream>
#include <string>

class Route {
private:
    std::string name;
    std::string tag;
    std::vector<std::shared_ptr<Crossing>> crossings;
    double distanceKm;
    double baseMinutes;

public:
    Route(std::string name, std::string tag, double distanceKm, double baseMinutes)
        : name(std::move(name)), tag(std::move(tag)),
          distanceKm(distanceKm), baseMinutes(baseMinutes) {}

    void addCrossing(std::shared_ptr<Crossing> c) {
        if (c) crossings.push_back(std::move(c));
    }

    double crossingDelayMinutes() const {
        double total = 0.0;
        for (const auto& c : crossings)
            total += c->expectedWaitSeconds() / 60.0;
        return total;
    }

    double totalMinutes() const { return baseMinutes + crossingDelayMinutes(); }

    int riskCount() const {
        int n = 0;
        for (const auto& c : crossings)
            if (c->getStatus() != GateStatus::OPEN) ++n;
        return n;
    }

    const std::string& getName()    const { return name; }
    const std::string& getTag()     const { return tag; }
    double             getDistanceKm() const { return distanceKm; }
    double             getBaseMinutes() const { return baseMinutes; }
    const std::vector<std::shared_ptr<Crossing>>& getCrossings() const { return crossings; }

    bool operator<(const Route& other) const {
        return totalMinutes() < other.totalMinutes();
    }

    friend std::ostream& operator<<(std::ostream& os, const Route& r) {
        os << "  Route: " << r.name << "  [" << r.tag << "]\n";
        os << "    Distance         : " << r.distanceKm << " km\n";
        os << "    Base travel time : " << r.baseMinutes << " min\n";
        os << "    Crossing delay   : " << r.crossingDelayMinutes() << " min\n";
        os << "    TOTAL TIME       : " << r.totalMinutes() << " min\n";
        os << "    Crossings on the way:\n";
        if (r.crossings.empty()) {
            os << "      (none - fully grade-separated)\n";
        } else {
            for (const auto& c : r.crossings) {
                os << "      - " << c->getName()
                   << "  [" << c->statusString() << "]"
                   << "  ~" << (c->expectedWaitSeconds() / 60.0) << " min\n";
            }
        }
        return os;
    }
};