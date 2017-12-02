#ifndef PROJECT_LIBXTIDE_H
#define PROJECT_LIBXTIDE_H

#include <string>
#include "MeasureUnit.h"

#ifndef LIB_XTIDE_H
#define LIB_XTIDE_H
#include <xtide/libxtide.hh>
#endif

#include "Station.h"

namespace mdr {
    class TidesAndCurrents {

    private:
        std::unique_ptr<libxtide::StationIndex> stationIndex;


    public:
        TidesAndCurrents();

        void addHarmonicsFile(std::string harmonicsFile);

        size_t stationCount();

        std::vector<std::string> stationNames();

        std::shared_ptr<Station> getStation(const char *name);

    };
}

#endif //PROJECT_LIBXTIDE_H
