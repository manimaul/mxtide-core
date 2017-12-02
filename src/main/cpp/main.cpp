#include <iostream>
#include "TidesAndCurrents.h"

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
        tnc.addHarmonicsFile(path);

        cout << "station count:" << tnc.stationCount() << endl;
        cout << "names:" << tnc.stationNames().back() << endl;

        {
            auto station = tnc.getStation("San Diego Bay Entrance, California Current");
            printStationInformation(station);
        }
        {
            auto station = tnc.getStation("station does not exist");
            printStationInformation(station);
        }

        exit(EXIT_SUCCESS);
    } else {
        cout << "Please supply path to tide harmonics file." << endl;
        exit(EXIT_FAILURE);
    }
}

