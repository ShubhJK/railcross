// Crossing.h — Abstract base class (Abstraction + Encapsulation)
#pragma once
#include <string>
#include <ostream>

enum class GateStatus { OPEN, CLOSING_SOON, CLOSED };

class Crossing {
protected:
    std::string id, name, city, state, zone, division, line, landmark, alternateRoute;
    int    avgWaitMinutes;
    int    dailyTrains;
    double latitude;
    double longitude;
    GateStatus status;
    int        secondsToNextChange;

public:
    Crossing(std::string id, std::string name, std::string city, std::string state,
             std::string zone, std::string division, std::string line,
             std::string landmark, std::string alternateRoute,
             int avgWaitMinutes, int dailyTrains,
             double latitude, double longitude,
             GateStatus status = GateStatus::OPEN,
             int secondsToNextChange = 60)
        : id(std::move(id)), name(std::move(name)), city(std::move(city)),
          state(std::move(state)), zone(std::move(zone)), division(std::move(division)),
          line(std::move(line)), landmark(std::move(landmark)),
          alternateRoute(std::move(alternateRoute)),
          avgWaitMinutes(avgWaitMinutes), dailyTrains(dailyTrains),
          latitude(latitude), longitude(longitude),
          status(status), secondsToNextChange(secondsToNextChange) {}

    virtual ~Crossing() = default;

    virtual int         expectedWaitSeconds() const = 0;
    virtual std::string typeName()            const = 0;

    const std::string& getId()             const { return id; }
    const std::string& getName()           const { return name; }
    const std::string& getCity()           const { return city; }
    const std::string& getState()          const { return state; }
    const std::string& getZone()           const { return zone; }
    const std::string& getDivision()       const { return division; }
    const std::string& getLine()           const { return line; }
    const std::string& getLandmark()       const { return landmark; }
    const std::string& getAlternateRoute() const { return alternateRoute; }
    int                getAvgWaitMinutes() const { return avgWaitMinutes; }
    int                getDailyTrains()    const { return dailyTrains; }
    double             getLatitude()       const { return latitude; }
    double             getLongitude()      const { return longitude; }
    GateStatus         getStatus()         const { return status; }
    int                getSecondsToNext()  const { return secondsToNextChange; }

    void setStatus(GateStatus s)      { status = s; }
    void setSecondsToNextChange(int s){ secondsToNextChange = s; }
    void tick()                       { if (secondsToNextChange > 0) --secondsToNextChange; }

    std::string statusString() const {
        switch (status) {
            case GateStatus::OPEN:         return "OPEN";
            case GateStatus::CLOSING_SOON: return "CLOSING";
            case GateStatus::CLOSED:       return "CLOSED";
        }
        return "UNKNOWN";
    }
};