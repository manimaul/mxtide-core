#include <iostream>
#include "TidesAndCurrents.h"
#include "Location.h"

using namespace mdr;
using namespace std;

TidesAndCurrents::TidesAndCurrents() {
    stationIndex = make_unique<libxtide::StationIndex>();
}

/**
 * Add a tidal harmonics file.
 *
 * @param harmonicsFile the absolute path to the tidal harmonics file.
 */
void TidesAndCurrents::addHarmonicsFile(string harmonicsFile) {
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
    transform(stationIndex->begin(), stationIndex->end(), names.begin(), [](libxtide::StationRef *each) -> string {
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

std::shared_ptr<Station> TidesAndCurrents::findNearestStation(double lat, double lng, StationType type) {
    auto locationInfo = LocationInfo {};
    auto closest = std::pair<libxtide::StationRef *, double> {nullptr, 40.75e6}; // earth circumference in meters

    for_each(stationIndex->begin(), stationIndex->end(), [&](libxtide::StationRef *ref) {
        Location::calculateLocationInfo(locationInfo, lat, lng, ref->coordinates.lat(), ref->coordinates.lng());
        if (type.equals(ref) && locationInfo.distanceMeters < closest.second) {
            closest = {ref, locationInfo.distanceMeters};
        }
    });

    if (nullptr != closest.first) {
        return make_shared<Station>(closest.first);
    }

    return nullptr;
}

vector<Station> TidesAndCurrents::findStationIn(double centerLat,
                                                double centerLng,
                                                double radiusMeters,
                                                StationType type) {
    auto locationInfo = LocationInfo {};

    vector<libxtide::StationRef *> stationRefs;
    copy_if(stationIndex->begin(), stationIndex->end(), back_inserter(stationRefs), [&](libxtide::StationRef *ref) {
        Location::calculateLocationInfo(locationInfo, centerLat, centerLng, ref->coordinates.lat(),
                                        ref->coordinates.lng());
        return type.equals(ref) && locationInfo.distanceMeters <= radiusMeters;
    });

    vector<Station> results;
    transform(stationRefs.begin(), stationRefs.end(), back_inserter(results), [](libxtide::StationRef *ref) -> Station {
        return Station(ref);
    });

    return results;
}

vector<Station>
TidesAndCurrents::findStationInBounds(double northLat,
                                      double eastLng,
                                      double southLat,
                                      double westLng,
                                      StationType type) {
    //todo:
    return vector<Station>();
}
