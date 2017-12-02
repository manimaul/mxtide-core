#include <iostream>
#include "TidesAndCurrents.h"

using namespace mdr;
using namespace std;

TidesAndCurrents::TidesAndCurrents() {
    stationIndex = std::make_unique<libxtide::StationIndex>();
}

/**
 * Add a tidal harmonics file.
 *
 * @param harmonicsFile the absolute path to the tidal harmonics file.
 */
void TidesAndCurrents::addHarmonicsFile(std::string harmonicsFile) {
    stationIndex->addHarmonicsFile(harmonicsFile.c_str());
}

/**
 * @return the tide station count.
 */
size_t TidesAndCurrents::stationCount() {
    return stationIndex->size();
}

vector<string> TidesAndCurrents::stationNames() {
    auto names = vector<string>(stationIndex->size());
    transform(stationIndex->begin(), stationIndex->end(), names.begin(), [](libxtide::StationRef* each) -> string {
        return string(each->name.aschar());
    });
    return names;
}

/**
 * Get station by name.
 *
 * @param name the station name.
 * @return the station or nullptr if it doesn't exist.
 */
shared_ptr<Station> TidesAndCurrents::getStation(const char *name) {
    libxtide::StationRef *stationRef = stationIndex->getStationRefByName(Dstr(name));
    if (stationRef) {
        return make_shared<Station>(stationRef);
    }
    return nullptr;
}
