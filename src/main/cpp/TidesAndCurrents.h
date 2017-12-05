#ifndef PROJECT_LIBXTIDE_H
#define PROJECT_LIBXTIDE_H

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

        void addHarmonicsFile(std::string harmonicsFile);

        size_t stationCount();

        std::vector<std::string> stationNames();

        Optional<Station> getStation(const char *name);

        Optional<Station> findNearestStation(double lat,
                                             double lng,
                                             StationType type);

        std::vector<Station> findStationIn(double centerLat,
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
        std::vector<Station> findStationInBounds(double northLat,
                                                 double eastLng,
                                                 double southLat,
                                                 double westLng,
                                                 StationType type);

    };
}

#endif //PROJECT_LIBXTIDE_H
