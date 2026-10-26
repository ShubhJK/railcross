# RailKross 🚦

## 🔗 Live Links
- **Live Website:** [https://railcross.onrender.com](https://railcross.onrender.com)
- **GitHub Repository:** [https://github.com/ShubhJK/railcross](https://github.com/ShubhJK/railcross)

## 📝 Project Description
India-focused railway level-crossing status & route-planning platform.
OOPS semester project in C++.
\# RailCross



India-focused railway level-crossing status \& route-planning platform.

OOPS semester project in C++. Focus region: Punjab / Patiala.



\## Structure

\- data/    JSON datasets

\- cpp/     C++ OOPS code + HTTP backend

\- web/     Frontend (HTML/CSS/JS)

\- build/   Compiled binaries

\- docs/    Report \& class diagram

\- screenshots/  Demo images



\## Build \& Run

CLI demo:

&#x20; g++ -std=c++17 -Icpp/include cpp/src/main.cpp cpp/src/DataStore.cpp -o build/railcross.exe



HTTP server:

&#x20; g++ -std=c++17 -O2 -D\_WIN32\_WINNT=0x0A00 -DWINVER=0x0A00 -Icpp/include -Icpp/third\_party cpp/server/server\_main.cpp cpp/server/Server.cpp cpp/src/DataStore.cpp -o build/server.exe -lws2\_32

