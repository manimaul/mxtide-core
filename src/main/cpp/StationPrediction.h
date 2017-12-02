#ifndef PROJECT_STATIONPREDICTION_H
#define PROJECT_STATIONPREDICTION_H

#include <string>
#include <chrono>

using DurationSeconds = std::chrono::seconds;
using SystemClock = std::chrono::system_clock;
using TimePoint = std::chrono::time_point<SystemClock, DurationSeconds>;

namespace mdr {

    static const char *dateTimeFormat = "%Y-%m-%d %H:%M %p %Z";

    template<typename T>
    struct StationPrediction {
        TimePoint timePoint;
        T value{};

        std::string formatTime(const char *format = dateTimeFormat) {
            time_t tt = std::chrono::system_clock::to_time_t(timePoint);
            size_t sz = 64;
            char buff[sz];
            strftime(buff, sz, format, localtime(&tt));
            return std::string(buff);
        }
    };
}

#endif //PROJECT_STATIONPREDICTION_H
