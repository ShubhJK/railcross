// ============================================================
// LiveDataFetcher.h — RailKit API client
// Endpoints: /api/v1/stations/:code/live and /api/v1/trains/:n/live/:date
// Auth: x-api-key header
// ============================================================
#pragma once
#include "httplib.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

using json = nlohmann::json;

class LiveDataFetcher {
private:
    std::string apiKey;
    std::string host;

    // Returns today's date as DD-MM-YYYY (IST-ish; uses local time)
    static std::string todayDDMMYYYY() {
        std::time_t t = std::time(nullptr);
        std::tm* tm = std::localtime(&t);
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << (tm->tm_mday) << "-"
           << std::setw(2) << std::setfill('0') << (tm->tm_mon + 1) << "-"
           << (tm->tm_year + 1900);
        return ss.str();
    }

public:
    LiveDataFetcher(const std::string& key)
        : apiKey(key), host("https://api.railkit.in") {}

    // -----------------------------------------------------------
    // Live at Station — trains currently at / arriving at a station
    // stnCode: e.g. "PTA" (Patiala), "RPJ" (Rajpura), "LDH" (Ludhiana)
    // hrs: 2, 4, or 8
    // -----------------------------------------------------------
    json fetchStationLive(const std::string& stnCode, int hrs = 2) {
        httplib::Client cli(host);
        cli.set_default_headers({
            { "x-api-key", apiKey },
            { "accept", "application/json" }
        });
        cli.set_connection_timeout(10, 0);
        cli.set_read_timeout(15, 0);

        std::string path = "/api/v1/stations/" + stnCode
                         + "/live?hrs=" + std::to_string(hrs);

        std::cerr << "[RailKit] GET " << host << path << "\n";

        auto res = cli.Get(path.c_str());
        if (!res) {
            std::cerr << "[RailKit] No response (network error)\n";
            return json::object();
        }
        if (res->status != 200) {
            std::cerr << "[RailKit] HTTP " << res->status
                      << " — body: " << res->body << "\n";
            return json::object();
        }
        try {
            return json::parse(res->body);
        } catch (const std::exception& e) {
            std::cerr << "[RailKit] JSON parse error: " << e.what() << "\n";
            return json::object();
        }
    }

    // -----------------------------------------------------------
    // Track Train Live — position of a specific train today
    // trainNumber: e.g. "14645"
    // -----------------------------------------------------------
    json fetchTrainLive(const std::string& trainNumber) {
        httplib::Client cli(host);
        cli.set_default_headers({
            { "x-api-key", apiKey },
            { "accept", "application/json" }
        });
        cli.set_connection_timeout(10, 0);
        cli.set_read_timeout(15, 0);

        std::string date = todayDDMMYYYY();
        std::string path = "/api/v1/trains/" + trainNumber
                         + "/live/" + date;

        std::cerr << "[RailKit] GET " << host << path << "\n";

        auto res = cli.Get(path.c_str());
        if (!res) {
            std::cerr << "[RailKit] No response (network error)\n";
            return json::object();
        }
        if (res->status != 200) {
            std::cerr << "[RailKit] HTTP " << res->status
                      << " — body: " << res->body << "\n";
            return json::object();
        }
        try {
            return json::parse(res->body);
        } catch (const std::exception& e) {
            std::cerr << "[RailKit] JSON parse error: " << e.what() << "\n";
            return json::object();
        }
    }

    // -----------------------------------------------------------
    // Get Train Info — static info about a train (name, route, etc.)
    // -----------------------------------------------------------
    json fetchTrainInfo(const std::string& trainNumber) {
        httplib::Client cli(host);
        cli.set_default_headers({
            { "x-api-key", apiKey },
            { "accept", "application/json" }
        });
        cli.set_connection_timeout(10, 0);
        cli.set_read_timeout(15, 0);

        std::string path = "/api/v1/trains/" + trainNumber + "/info";
        auto res = cli.Get(path.c_str());

        if (!res || res->status != 200) return json::object();
        try { return json::parse(res->body); }
        catch (...) { return json::object(); }
    }
};