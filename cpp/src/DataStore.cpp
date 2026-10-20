// DataStore.cpp — Punjab / Patiala dataset
#include "DataStore.h"
#include "LevelCrossing.h"

using LC = LevelCrossing;

std::vector<std::shared_ptr<Crossing>> DataStore::loadCrossings() {
    return {
        std::make_shared<LC>(
            "PB-PTA-020", "20 No. Phatak (Crossing No. 20)",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Rajpura-Bathinda Line", "Baradari Garden area",
            "Baradari Garden Flyover / Mall Road Bypass",
            9, 48, 30.3398, 76.3869, GateStatus::OPEN, 58),

        std::make_shared<LC>(
            "PB-PTA-021", "21 No. Phatak (Crossing No. 21)",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Rajpura-Bathinda Line", "Near Dukhniwaran Sahib Gurudwara",
            "Sirhind Road Bypass",
            8, 46, 30.3450, 76.3920, GateStatus::OPEN, 41),

        

        std::make_shared<LC>(
            "PB-PTA-023", "23 No. Phatak (Crossing No. 23)",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Rajpura-Bathinda Line", "Model Town, near Patiala Cantt Station",
            "Model Town Flyover",
            9, 50, 30.3510, 76.4020, GateStatus::CLOSING_SOON, 19),

        std::make_shared<LC>(
            "PB-PTA-024", "24 No. Phatak (Crossing No. 24)",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Rajpura-Bathinda Line", "Near Patiala Cantt Station, Model Town",
            "Patiala Cantt Road / Sangrur Bypass",
            11, 54, 30.3530, 76.4050, GateStatus::OPEN, 33),

        std::make_shared<LC>(
            "PB-PTA-016", "Crossing No. 16",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Rajpura-Bathinda Line", "Patiala city",
            "City Bypass Road",
            8, 44, 30.3290, 76.3790, GateStatus::OPEN, 64),

        std::make_shared<LC>(
            "PB-PTA-019", "Crossing No. 19",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Rajpura-Bathinda Line", "Patiala city",
            "City Bypass Road",
            8, 44, 30.3340, 76.3830, GateStatus::CLOSED, 124),

        std::make_shared<LC>(
            "PB-PTA-SAMANA", "Patiala-Samana Road Crossing",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Patiala-Samana Branch", "Patiala-Samana Road",
            "Sangrur Road Bypass",
            7, 22, 30.3012, 76.4012, GateStatus::OPEN, 47),

        std::make_shared<LC>(
            "PB-PTA-RAJPURA", "Patiala-Rajpura Road Gate",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Rajpura-Bathinda Main Line", "Patiala-Rajpura Road",
            "Rajpura Bypass via NH-44",
            11, 52, 30.3601, 76.4230, GateStatus::CLOSING_SOON, 23),

        std::make_shared<LC>(
            "PB-PTA-SANGRUR", "Sangrur Road Crossing",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Patiala-Sangrur Branch", "Sangrur Road, Patiala",
            "Sangrur Bypass via Bhawanigarh",
            6, 18, 30.2765, 76.3680, GateStatus::OPEN, 72),

        std::make_shared<LC>(
            "PB-PTA-CANAL", "Canal Level Crossing",
            "Patiala", "Punjab", "Northern Railway", "Ambala",
            "Rajpura-Bathinda Line", "Ranbirpura / Dhamo Majra",
            "Canal Road Bypass",
            7, 30, 30.3120, 76.3710, GateStatus::OPEN, 55),

        std::make_shared<LC>(
            "PB-RAJ-001", "Rajpura Junction Gate",
            "Rajpura", "Punjab", "Northern Railway", "Ambala",
            "Delhi-Amritsar Main Line", "Rajpura Junction",
            "Rajpura Bypass / NH-44",
            11, 58, 30.4833, 76.5945, GateStatus::CLOSED, 98),

        std::make_shared<LC>(
            "PB-SIR-001", "Sirhind-Barara LC 113/CE",
            "Sirhind", "Punjab", "Northern Railway", "Ambala",
            "Barara-Tandwal Section", "Sirhind",
            "NH-44 Bypass via Rajpura",
            8, 32, 30.6432, 76.3821, GateStatus::OPEN, 61),

        std::make_shared<LC>(
            "PB-LDH-001", "Ludhiana-Jalandhar LC C-43",
            "Ludhiana", "Punjab", "Northern Railway", "Firozpur",
            "Jalandhar-Hoshiarpur Line", "Ludhiana city",
            "Ferozepur Road Flyover",
            8, 40, 30.9010, 75.8573, GateStatus::OPEN, 38),

        std::make_shared<LC>(
            "PB-JAL-001", "Jalandhar-Amritsar LC C-124",
            "Jalandhar", "Punjab", "Northern Railway", "Firozpur",
            "Ludhiana-Amritsar Line", "Jalandhar city",
            "Kapurthala Road Bypass",
            12, 44, 31.3260, 75.5762, GateStatus::CLOSED, 76),

        std::make_shared<LC>(
            "PB-ASR-001", "Amritsar-Pathankot LC C-9",
            "Amritsar", "Punjab", "Northern Railway", "Firozpur",
            "Amritsar-Pathankot Line", "Amritsar city",
            "GT Road Bypass / NH-354",
            10, 36, 31.6340, 74.8723, GateStatus::OPEN, 69),

        std::make_shared<LC>(
            "PB-BTI-001", "Bathinda-Delhi LC B/87",
            "Bathinda", "Punjab", "Northern Railway", "Ambala",
            "Bathinda-Delhi Main Line", "Bathinda city",
            "Barnala Bypass",
            10, 50, 30.2110, 74.9455, GateStatus::CLOSING_SOON, 28),

        std::make_shared<LC>(
            "PB-DOR-001", "Doraha LC 164A",
            "Doraha", "Punjab", "Northern Railway", "Firozpur",
            "Ambala-Ludhiana Section", "Doraha",
            "Doraha ROB / NH-44",
            13, 56, 30.7998, 76.0201, GateStatus::CLOSED, 142),
    };
}

std::vector<City> DataStore::loadCities() {
    return {
        { "Patiala",    30.3398, 76.3869 },
        { "Rajpura",    30.4833, 76.5945 },
        { "Sirhind",    30.6432, 76.3821 },
        { "Sangrur",    30.2458, 75.8421 },
        { "Ludhiana",   30.9010, 75.8573 },
        { "Jalandhar",  31.3260, 75.5762 },
        { "Amritsar",   31.6340, 74.8723 },
        { "Bathinda",   30.2110, 74.9455 },
        { "Doraha",     30.7998, 76.0201 },
        { "Chandigarh", 30.7333, 76.7794 },
        { "Mohali",     30.7046, 76.7179 },
        { "Moga",       30.8158, 75.1717 },
        { "Firozpur",   30.9331, 74.6225 },
        { "Pathankot",  32.2643, 75.6421 },
        { "Hoshiarpur", 31.5143, 75.9115 },
        { "Ambala",     30.3782, 76.7767 },
    };
}