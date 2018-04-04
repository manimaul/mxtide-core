#pragma once

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
        libxtide::StationRef *stationRef = nullptr;
        libxtide::Station *station = nullptr;

        libxtide::Station *getStation();

        void setStationUnits(MeasureUnit &unit);

        static float currentStationValue(float value, libxtide::Units::PredictionUnits &srcUnit, MeasureUnit &dstUnit);

    public:
        Station() = default;

        Station(Station &station) = default;

        Station(Station &&station) = default;

        explicit Station(libxtide::StationRef *stationRef);

        virtual ~Station();

        static TimePoint now();

        static DurationSeconds twentyFourHours();

        /**
         * @return the station latitude.
         */
        const double getLatitude();

        /**
         * @return the station longitude.
         */
        const double getLongitude();

        /**
         * @return the time zone of the station.
         */
        const std::string timeZone();

        /**
         * @return the name of the station.
         */
        const std::string name();

        /**
         * @param epoch your local time.
         * @return the the station's time-zone formatted time converted from your local time.
         */
        std::string getTimeStamp(TimePoint epoch = now());

        /**
         * Get a tidal prediction for a window of time containing a float value representing the tide or current level.
         *
         * @param epoch the time point of the prediction window start
         * @param duration the length of the prediction window
         * @param unit measurement unit in meters/kph , feet/mph, feet/kts
         * @return the tidal prediction
         */
        std::vector<StationPrediction<float>> getPredictionRaw(TimePoint epoch = now(),
                                                               DurationSeconds duration = twentyFourHours(),
                                                               MeasureUnit unit = metric);

        /**
         * @return the type of station.
         */
        StationType type();
    };
}
