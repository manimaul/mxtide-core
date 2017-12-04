#include <iostream>
#include "TidesAndCurrents.h"
#include "PerfTimer.h"

using namespace mdr;
using namespace std;

void printStationInformation(const shared_ptr<Station> &station) {
    if (nullptr != station) {
        cout << "Station name: " << station->name() << endl;
        cout << "Station tz: " << station->timeZone() << endl;
        cout << "Station type: " << station->type().toString() << endl;
        cout << "Station latitude: " << station->getLatitude() << " longitude: " << station->getLongitude() << endl;
        cout << "Station timestamp" << station->getTimeStamp() << endl;

        auto plainPrediction = station->getPredictionPlain();
        cout << "Station plain prediction: " << endl;
        for_each(plainPrediction.begin(), plainPrediction.end(), [] (StationPrediction<string> &data) {
            cout << data.formatTime() << " ------value-----> " << data.value << endl;
        });

        auto rawPrediction = station->getPredictionRaw();
        cout << "Station raw prediction: " << endl;
        for_each(rawPrediction.begin(), rawPrediction.end(), [] (StationPrediction<float> &data) {
            cout << data.formatTime() << " ------value-----> " << data.value << endl;
        });

//        cout << "Station clock prediction SVG: " << station->getPredictionClockSVG() << endl;
    }
}

int main(int argc, char** argv) {
    if (argc == 2) {
        auto path = string(argv[1]);
        auto tnc = TidesAndCurrents();
        auto pt = PerfTimer();
        tnc.addHarmonicsFile(path);
        pt.stop("adding harmonics");

        pt.resetStart();
        auto waStations = tnc.findStationInBounds(49, -117, 45.4, -125, stationTypeTide);
        pt.stop("finding WA region stations");
        cout << "WA region stations: " << waStations.size() << endl;
//        for_each(waStations.begin(), waStations.end(), [](Station &station) {
//           cout << "station name: " << station.name() << endl;
//        });

        double lat = 47;
        double lng = -122;
        double radius = 100000;
        pt.resetStart();
        auto stations = tnc.findStationIn(lat, lng, radius, stationTypeTide);
        pt.stop("finding stations with radius");

        pt.resetStart();
        auto nearestTide = tnc.findNearestStation(lat, lng, stationTypeTide);
        pt.stop("finding nearest tide station");

        pt.resetStart();
        nearestTide->getPredictionRaw();
        pt.stop("nearest station raw");

        pt.resetStart();
        nearestTide->getPredictionRaw();
        pt.stop("nearest station raw subsequent");

        pt.resetStart();
        auto nearestByName = tnc.getStation(nearestTide->name().c_str());
        pt.stop("nearest station re-fetched by name");

        pt.resetStart();
        nearestByName->getPredictionRaw();
        pt.stop("nearest station re-fetched raw subsequent");


//        printStationInformation(nearestTide);
        auto nearestCurrent = tnc.findNearestStation(lat, lng, stationTypeCurrent);
//        printStationInformation(nearestCurrent);

//        cout << "station count:" << stations.size() << endl;

//        cout << "station count:" << tnc.stationCount() << endl;
//        cout << "names:" << tnc.stationNames().back() << endl;

//        {
//            auto station = tnc.getStation("San Diego Bay Entrance, California Current");
//            printStationInformation(station);
//        }
//        {
//            auto station = tnc.getStation("station does not exist");
//            printStationInformation(station);
//        }

        exit(EXIT_SUCCESS);
    } else {
        cout << "Please supply path to tide harmonics file." << endl;
        exit(EXIT_FAILURE);
    }
}

