#include <chrono>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "Station.h"

using namespace std;
using namespace mdr;
using namespace std::chrono;

Station::Station(libxtide::StationRef *stationRef) : stationRef(stationRef) {}

vector<string> split(const char *str, char delimiter) {
    auto tokens = vector<string>();
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void Station::setStationUnits(MeasureUnit &unit) {
    switch (unit) {
        case metric:
            getStation()->setUnits(libxtide::Units::meters);
            break;
        case statute:
            getStation()->setUnits(libxtide::Units::feet);
            break;
        case nautical:
            if (getStation()->isCurrent) {
                getStation()->setUnits(libxtide::Units::knots);
            } else {
                getStation()->setUnits(libxtide::Units::feet);
            }
            break;
    }
}

const double Station::getLatitude() {
    return stationRef->coordinates.lat();
}

const double Station::getLongitude() {
    return stationRef->coordinates.lng();
}

TimePoint Station::now() {
    auto now = SystemClock::now();
    return chrono::time_point_cast<chrono::seconds>(now);
}

DurationSeconds Station::twentyFourHours() {
    return DurationSeconds(60 * 60 * 24);
}

const string Station::timeZone() {
    auto tz = string(stationRef->timezone.aschar());
    tz.erase(std::remove(tz.begin(), tz.end(), ':'), tz.end());
    return tz;
}

const string Station::name() {
    auto name = stationRef->name;
    return string(name.utf8().aschar());
}

string Station::getTimeStamp(TimePoint epoch) {
    auto t = libxtide::Timestamp(SystemClock::to_time_t(epoch));
    auto s = Dstr{};
    t.print(s, stationRef->timezone);
    return s.aschar();
}


float Station::currentStationValue(float value, libxtide::Units::PredictionUnits &srcUnit, MeasureUnit &dstUnit) {
    if (srcUnit == dstUnit) {
        return value;
    }
    float kts = value;
    if (srcUnit == libxtide::Units::PredictionUnits::knotsSquared) {
        // This is not mathematically correct, but it is tidematically correct.
        if (value < 0) {
            kts = -sqrt(fabs(kts));
        } else {
            kts = sqrt(kts);
        }
    } else if (srcUnit != libxtide::Units::PredictionUnits::knots) {
        throw std::runtime_error { "unexpected tide station units" };
    }

    switch (dstUnit) {
        case metric:
            return kts * 1.852f; // kph
        case statute:
            return kts * 1.15078f; //mph
        default:
        case nautical:
            return kts;
    }
}

vector<StationPrediction<float>>
Station::getPredictionRaw(TimePoint epoch, DurationSeconds duration, MeasureUnit unit) {
    bool isCurrent = getStation()->isCurrent;
    if (!isCurrent) {
        setStationUnits(unit); // only sets length units
    }
    auto srcUnit = getStation()->predictUnits();
    auto start = libxtide::Timestamp(SystemClock::to_time_t(epoch));
    auto end = libxtide::Timestamp(SystemClock::to_time_t(epoch + duration));
    Dstr dstr = {};

    getStation()->print(dstr, start, end, libxtide::Mode::raw, libxtide::Format::text);
    auto lines = split(dstr.aschar(), '\n');

    vector<StationPrediction<float>> predictionData;
    transform(lines.begin(), lines.end(), back_inserter(predictionData),
              [&isCurrent, &srcUnit, &unit](string &str) -> StationPrediction<float> {
                  auto pair = split(str.c_str(), ' ');
                  assert(pair.size() == 2);
                  float value = stof(pair.back());
                  if (isCurrent) {
                      value = currentStationValue(value, srcUnit, unit);
                  }
                  auto timePoint = TimePoint(seconds(stoll(pair.front())));
                  return StationPrediction<float>{timePoint, value};
              });
    return predictionData;
}

StationType Station::type() {
    if (getStation()->isCurrent) {
        return stationTypeCurrent;
    } else {
        return stationTypeTide;
    }
}

libxtide::Station *Station::getStation() {
    if (nullptr == station) {
        station = stationRef->load();
    }
    return station;
}

Station::~Station() {
    delete station;
}
