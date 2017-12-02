#ifndef PROJECT_STATION_H
#define PROJECT_STATION_H

#include <string>

#ifndef LIB_XTIDE_H
#define LIB_XTIDE_H

#include <xtide/libxtide.hh>

#endif

#include "MeasureUnit.h"
#include "StationType.h"
#include "StationPrediction.h"


namespace mdr {

    class Station {

    private:
        std::unique_ptr<libxtide::Station> station{};

    public:
        explicit Station(libxtide::StationRef *stationRef);

        static TimePoint now();

        static DurationSeconds twentyFourHours();

        const double getLatitude();

        const double getLongitude();

        const std::string timeZone();

        const std::string name();

        std::string getTimeStamp(TimePoint epoch = now());

        std::vector<StationPrediction<float>> getPredictionRaw(TimePoint epoch = now(),
                                                               DurationSeconds duration = twentyFourHours(),
                                                               MeasureUnit unit = meters);

        std::vector<StationPrediction<std::string>> getPredictionPlain(TimePoint epoch = now(),
                                                               DurationSeconds duration = twentyFourHours(),
                                                               MeasureUnit unit = meters);

        std::string getPredictionClockSVG(TimePoint epoch = now(),
                                          DurationSeconds duration = twentyFourHours(),
                                          MeasureUnit unit = meters);

        StationType type();
    };
}

#endif //PROJECT_STATION_H
