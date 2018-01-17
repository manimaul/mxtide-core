#pragma once

#include <string>
#include "MeasureUnit.h"

#ifndef LIB_XTIDE_H
#define LIB_XTIDE_H

#include <xtide/libxtide.hh>

#endif

#include "Station.h"
#include "Optional.h"

namespace mdr {
    class TidesAndCurrents {

    private:
        std::unique_ptr<libxtide::StationIndex> stationIndex;


    public:
        TidesAndCurrents();

        /**
         * Add the stations from a harmonics file.
         *
         * @param harmonicsFile the absolute path of the file.
         */
        void addHarmonicsFile(std::string harmonicsFile);

        /**
         * @return the number of stations.
         */
        size_t stationCount();

        /**
         * @return a list of station names.
         */
        std::vector<std::string> stationNames();

        /**
         * Find a station by its exact name.
         * @param name the exact name of the station.
         * @return an optional station.
         */
        Optional<Station> findStationByName(const char *name);

        /**
         * Find a station nearest to a position.
         *
         * @param lat latitude
         * @param lng longitude
         * @param type
         * @return an optional nearest station.
         */
        Optional<Station> findNearestStation(double lat,
                                             double lng,
                                             StationType type);

       /**
        * Find the nearest stations sorted by distance
        *
        * @param lat your latitude
        * @param lng your longitude
        * @param type the type of the stations to find
        * @return the list of closest stations sorted by distance to the provided position
        */
        std::vector<Station> findNearestStations(double lat,
                                                 double lng,
                                                 StationType type);
        /**
         * Find stations within a circle.
         *
         * @param centerLat the center point latitude
         * @param centerLng the center point longitude
         * @param radiusMeters the circle radius in meters
         * @param type the type of stations to find
         * @return a list of stations within the specified circle.
         */
        std::vector<Station> findStationsInCircle(double centerLat,
                                                  double centerLng,
                                                  double radiusMeters,
                                                  StationType type);

        /**
         * Find stations within a bounding box. Note: the bounding box cannot span the international dateline.
         *
         * @param northLat the north most latitude
         * @param eastLng the east most longitude
         * @param southLat the south most latitude
         * @param westLng the west most longitude
         * @param type the station type
         * @return a list of stations within the specified bounds.
         */
        std::vector<Station> findStationsInBounds(double northLat,
                                                  double eastLng,
                                                  double southLat,
                                                  double westLng,
                                                  StationType type);

    };
}
