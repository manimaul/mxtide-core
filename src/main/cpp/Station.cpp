#include <chrono>
#include <sstream>
#include "Station.h"

using namespace std;
using namespace mdr;
using namespace std::chrono;

Station::Station(libxtide::StationRef *stationRef) : stationRef(stationRef) {}

vector<string> split(const char* str, char delimiter) {
    auto tokens = vector<string>();
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
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
    return string(stationRef->timezone.aschar());
}

const string Station::name() {
    return string(stationRef->name.aschar());
}

string Station::getTimeStamp(TimePoint epoch)  {
    auto t = libxtide::Timestamp(SystemClock::to_time_t(epoch));
    auto s = Dstr{};
    t.print(s, stationRef->timezone);
    return s.aschar();
}

vector<StationPrediction<float>> Station::getPredictionRaw(TimePoint epoch, DurationSeconds duration, MeasureUnit unit) {
    switch (unit) {
        case meters:
            getStation()->setUnits(libxtide::Units::meters);
        case feet:
            getStation()->setUnits(libxtide::Units::feet);
    }
    auto start = libxtide::Timestamp(SystemClock::to_time_t(epoch));
    auto end = libxtide::Timestamp(SystemClock::to_time_t(epoch + duration));
    Dstr dstr = {};

    getStation()->print(dstr, start, end, libxtide::Mode::raw, libxtide::Format::text);
    auto lines = split(dstr.aschar(), '\n');

    vector<StationPrediction<float>> predictionData;
    transform(lines.begin(), lines.end(), back_inserter(predictionData), [](string &str) -> StationPrediction<float> {
        auto pair = split(str.c_str(), ' ');
        assert(pair.size() == 2);
        auto value = stof(pair.back());
        auto timePoint = TimePoint(seconds(stoll(pair.front())));
        return StationPrediction<float> { timePoint, value };
    });
    return predictionData;
}

vector<StationPrediction<string>> Station::getPredictionPlain(TimePoint epoch, DurationSeconds duration, MeasureUnit unit) {
    switch (unit) {
        case meters:
            getStation()->setUnits(libxtide::Units::meters);
        case feet:
            getStation()->setUnits(libxtide::Units::feet);
    }
    auto start = libxtide::Timestamp(SystemClock::to_time_t(epoch));
    auto end = libxtide::Timestamp(SystemClock::to_time_t(epoch + duration));
    Dstr dstr = {};

    getStation()->print(dstr, start, end, libxtide::Mode::plain, libxtide::Format::CSV);
    auto lines = split(dstr.aschar(), '\n');
    vector<StationPrediction<string>> predictionData;
    transform(lines.begin(), lines.end(), back_inserter(predictionData), [](string &str) -> StationPrediction<string> {
        auto tuple = split(str.c_str(), ',');
        auto dateString = tuple[1] + " " +  tuple[2];
        std::tm tm = {};
        strptime(dateString.c_str(), dateTimeFormat, &tm);
        auto timePoint = time_point_cast<seconds>(system_clock::from_time_t(std::mktime(&tm)));
        return StationPrediction<string> { timePoint, tuple.back() };

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

string Station::getPredictionClockSVG(TimePoint epoch, DurationSeconds duration, MeasureUnit unit) {
    switch (unit) {
        case meters:
            getStation()->setUnits(libxtide::Units::meters);
        case feet:
            getStation()->setUnits(libxtide::Units::feet);
    }
    auto start = libxtide::Timestamp(SystemClock::to_time_t(epoch));
    auto end = libxtide::Timestamp(SystemClock::to_time_t(epoch + duration));
    Dstr dstr = {};
    getStation()->print(dstr, start, end, libxtide::Mode::graph, libxtide::Format::SVG);
    return dstr.aschar();
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
