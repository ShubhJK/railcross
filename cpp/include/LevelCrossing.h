// LevelCrossing.h — Derived class (Inheritance + Polymorphism)
#pragma once
#include "Crossing.h"

class LevelCrossing : public Crossing {
public:
    LevelCrossing(std::string id, std::string name, std::string city, std::string state,
                  std::string zone, std::string division, std::string line,
                  std::string landmark, std::string alternateRoute,
                  int avgWaitMinutes, int dailyTrains,
                  double latitude, double longitude,
                  GateStatus status = GateStatus::OPEN,
                  int secondsToNextChange = 60)
        : Crossing(std::move(id), std::move(name), std::move(city), std::move(state),
                   std::move(zone), std::move(division), std::move(line),
                   std::move(landmark), std::move(alternateRoute),
                   avgWaitMinutes, dailyTrains, latitude, longitude,
                   status, secondsToNextChange) {}

    int expectedWaitSeconds() const override {
        switch (status) {
            case GateStatus::OPEN:
                return static_cast<int>(avgWaitMinutes * 60 * 0.35);
            case GateStatus::CLOSING_SOON:
                return static_cast<int>(avgWaitMinutes * 60 * 0.80 + 90);
            case GateStatus::CLOSED:
                return secondsToNextChange +
                       static_cast<int>(avgWaitMinutes * 60 * 0.45);
        }
        return 0;
    }

    std::string typeName() const override { return "Level Crossing"; }
};