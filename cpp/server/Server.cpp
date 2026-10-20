// ============================================================
// Server.cpp — HTTP routes: static files + JSON API
// Live data via RailRadar + simulation fallback
// ============================================================
#include "Server.h"
#include "JsonSerializer.h"
#include "LiveDataFetcher.h"
#include "httplib.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <cstdlib>

RailServer::RailServer(std::vector<std::shared_ptr<Crossing>> cs,
                       std::vector<City> ct,
                       std::string wr,
                       int p)
    : crossings(std::move(cs)), cities(std::move(ct)),
      webRoot(std::move(wr)), port(p) {}

void RailServer::run() {
    httplib::Server svr;

    // CORS for local testing
    svr.set_post_routing_handler([](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });
    svr.Options(R"(.*)", [](const httplib::Request&, httplib::Response& res) {
        res.status = 204;
    });

    // --------------------------------------------------------------
    // GET /api/crossings — all crossings as JSON
    // --------------------------------------------------------------
    svr.Get("/api/crossings", [this](const httplib::Request&, httplib::Response& res) {
        res.set_content(RailJson::crossingsToJson(crossings).dump(), "application/json");
    });

    // --------------------------------------------------------------
    // GET /api/cities — all cities for route planner
    // --------------------------------------------------------------
    svr.Get("/api/cities", [this](const httplib::Request&, httplib::Response& res) {
        res.set_content(RailJson::citiesToJson(cities).dump(), "application/json");
    });

    // --------------------------------------------------------------
    // GET /api/plan?from=X&to=Y — ranked routes
    // --------------------------------------------------------------
    svr.Get("/api/plan", [this](const httplib::Request& req, httplib::Response& res) {
        if (!req.has_param("from") || !req.has_param("to")) {
            res.status = 400;
            res.set_content(R"({"error":"missing 'from' or 'to' parameter"})", "application/json");
            return;
        }
        std::string from = req.get_param_value("from");
        std::string to   = req.get_param_value("to");

        RoutePlanner planner(crossings, cities);
        auto routes = planner.plan(from, to);
        std::sort(routes.begin(), routes.end());

        json out = RailJson::routesToJson(routes);
        out["from"] = from;
        out["to"]   = to;
        res.set_content(out.dump(), "application/json");
    });

    // --------------------------------------------------------------
    // GET /api/simulate — advance a random crossing (simulation mode)
    // --------------------------------------------------------------
    svr.Get("/api/simulate", [this](const httplib::Request&, httplib::Response& res) {
        if (crossings.empty()) {
            res.status = 404;
            res.set_content(R"({"error":"no crossings loaded"})", "application/json");
            return;
        }
        static std::mt19937 rng{std::random_device{}()};
        std::uniform_int_distribution<size_t> dist(0, crossings.size() - 1);
        auto c = crossings[dist(rng)];

        GateStatus old = c->getStatus();
        GateStatus next = GateStatus::OPEN;
        int nextSecs = 60;
        switch (old) {
            case GateStatus::OPEN:
                next = GateStatus::CLOSING_SOON;
                nextSecs = 20 + static_cast<int>(rng() % 15);
                break;
            case GateStatus::CLOSING_SOON:
                next = GateStatus::CLOSED;
                nextSecs = 60 + static_cast<int>(rng() % 100);
                break;
            case GateStatus::CLOSED:
                next = GateStatus::OPEN;
                nextSecs = 40 + static_cast<int>(rng() % 60);
                break;
        }
        c->setStatus(next);
        c->setSecondsToNextChange(nextSecs);

        json out = {
            { "affected", RailJson::crossingToJson(c) },
            { "message",  "Crossing " + c->getName() + " advanced." }
        };
        res.set_content(out.dump(), "application/json");
    });

    // --------------------------------------------------------------
    // GET /api/live-station?stn=PTA&hrs=2 — Secure Proxy to RailRadar
    // --------------------------------------------------------------
    svr.Get("/api/live-station", [](const httplib::Request& req, httplib::Response& res) {
        const char* key = std::getenv("RAILRADAR_API_KEY");
        if (!key || std::string(key).empty()) {
            res.status = 503;
            res.set_content(R"({"error":"RAILRADAR_API_KEY not set in Render Environment Variables."})", "application/json");
            return;
        }
        std::string stn = req.has_param("stn") ? req.get_param_value("stn") : "PTA";
        int hrs = req.has_param("hrs") ? std::stoi(req.get_param_value("hrs")) : 2;

        httplib::Client cli("https://api.railradar.in");
        cli.set_default_headers({
            { "Authorization", "Bearer " + std::string(key) },
            { "accept", "application/json" }
        });
        
        std::string path = "/v1/stations/" + stn + "/live?hours=" + std::to_string(hrs);
        auto api_res = cli.Get(path.c_str());

        if (api_res && api_res->status == 200) {
            res.set_content(api_res->body, "application/json");
        } else {
            res.status = 502;
            res.set_content(R"({"error":"Failed to fetch from RailRadar API. Check Render logs."})", "application/json");
        }
    });

    // --------------------------------------------------------------
    // GET /api/health — server status + current data mode
    // --------------------------------------------------------------
    svr.Get("/api/health", [this](const httplib::Request&, httplib::Response& res) {
        const char* key = std::getenv("RAILRADAR_API_KEY");
        bool liveMode = (key && std::string(key).length() > 0);

        json out = {
            { "status",     "ok" },
            { "crossings",  crossings.size() },
            { "cities",     cities.size() },
            { "service",    "RailCross C++ Backend" },
            { "version",    "1.0" },
            { "data_mode",  liveMode ? "LIVE (RailRadar)" : "SIMULATION" }
        };
        res.set_content(out.dump(), "application/json");
    });

    // --------------------------------------------------------------
    // Serve static website files from webRoot
    // --------------------------------------------------------------
    svr.set_mount_point("/", webRoot);
    svr.set_file_extension_and_mimetype_mapping("html", "text/html");
    svr.set_file_extension_and_mimetype_mapping("css",  "text/css");
    svr.set_file_extension_and_mimetype_mapping("js",   "application/javascript");
    svr.set_file_extension_and_mimetype_mapping("svg",  "image/svg+xml");

    std::cout << "\n  RailCross backend running\n";
    std::cout << "     Local   : http://localhost:" << port << "/\n";
    std::cout << "     API base: http://localhost:" << port << "/api/\n";
    std::cout << "     Serving : " << webRoot << "\n";

    const char* key = std::getenv("RAILRADAR_API_KEY");
    if (key && std::string(key).length() > 0) {
        std::cout << "     Mode    : LIVE (RailRadar API)\n";
    } else {
        std::cout << "     Mode    : SIMULATION (set RAILRADAR_API_KEY to go live)\n";
    }
    std::cout << "     Press Ctrl + C to stop.\n\n";

    svr.listen("0.0.0.0", port);
}
