#include <iostream>
#include "TidesAndCurrents.h"
#include "PerfTimer.h"

using namespace mdr;
using namespace std;

void printStationInformation(Optional<Station> &station) {
    station.let([] (Station &station) {
        cout << "Station name: " << station.name() << endl;
        cout << "Station tz: " << station.timeZone() << endl;
        cout << "Station type: " << station.type().toString() << endl;
        cout << "Station latitude: " << station.getLatitude() << " longitude: " << station.getLongitude() << endl;
        cout << "Station timestamp" << station.getTimeStamp() << endl;


        auto rawPrediction = station.getPredictionRaw();
        cout << "Station raw prediction: " << endl;
        for_each(rawPrediction.begin(), rawPrediction.end(), [](StationPrediction<float> &data) {
            cout << data.formatTime() << " ------value-----> " << data.value << endl;
        });
    });
}

int main(int argc, char **argv) {
    if (argc == 2) {
        auto path = string(argv[1]);
        auto tnc = TidesAndCurrents();
        auto pt = PerfTimer();
        tnc.addHarmonicsFile(path);
        pt.stop("adding harmonics");

        auto sorted = tnc.findNearestStations(49, -117, stationTypeTide);
        for_each(sorted.begin(), sorted.begin() + 10, [](Station &station) {
           cout << "station name: " << station.name() << endl;
        });

        double lat = 47;
        double lng = -122;
        double radius = 100000;
        pt.resetStart();
        auto stations = tnc.findStationsInCircle(lat, lng, radius, stationTypeTide);
        pt.stop("finding stations with radius");

        pt.resetStart();
        auto nearestTide = tnc.findNearestStation(lat, lng, stationTypeTide);
        pt.stop("finding nearest tide station");

        pt.resetStart();

        nearestTide.let([&](Station &station) {
            station.getPredictionRaw();
            pt.stop("nearest station raw");
        });

        string nearestTideName = {};
        nearestTide.let([&](Station &station) {
            pt.resetStart();
            station.getPredictionRaw();
            pt.stop("nearest station raw subsequent");
            nearestTideName = station.name();
        });

        pt.resetStart();
        auto nearestByName = tnc.findStationByName(nearestTideName.c_str(), stationTypeTide);
        pt.stop("nearest station re-fetched by name");

        pt.resetStart();
        nearestByName.let([](Station &station) {
            station.getPredictionRaw();
        });

        nearestByName.ifLetElse([&](Station &station) {
            station.getPredictionRaw();
            pt.stop("nearest by name station re-fetched raw subsequent");
        }, [&]() {
            pt.stop("nearest by name station was empty");
        });

        printStationInformation(nearestTide);
        auto nearestCurrent = tnc.findNearestStation(lat, lng, stationTypeCurrent);
        printStationInformation(nearestCurrent);

        cout << "station count:" << stations.size() << endl;
        cout << "station count:" << tnc.stationCount() << endl;

//        auto names = tnc.stationNames();
//        for_each(names.begin(), names.end(), [](string &name) {
//            cout << "name: " << name << endl;
//        });

//        {
//            auto station = tnc.findStationByName("San Diego Bay Entrance, California Current");
//            printStationInformation(station);
//        }
//        {
//            auto station = tnc.findStationByName("station does not exist");
//            printStationInformation(station);
//        }

        exit(EXIT_SUCCESS);
    } else {
        cout << "Please supply path to tide harmonics file." << endl;
        exit(EXIT_FAILURE);
    }
}

