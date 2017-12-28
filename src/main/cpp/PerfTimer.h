#pragma once

#include <chrono>
#include <iostream>

using PerfDuration = std::chrono::nanoseconds;
using SteadyClock = std::chrono::steady_clock;
using PerfTimePoint = std::chrono::time_point<SteadyClock, PerfDuration>;

namespace mdr {

    class PerfTimer {
    private:
        PerfTimePoint tp = std::chrono::steady_clock::now();

    public:
        void resetStart() {
            tp = std::chrono::steady_clock::now();
        }

        void stop(const char* message) {
            PerfTimePoint end = std::chrono::steady_clock::now();
            auto diff = end - tp;
            auto d = std::chrono::duration_cast<PerfDuration>(diff);
            std::cout << message << " : " << d.count() / 1000000.0 << "ms" << std::endl;
        }
    };
}
