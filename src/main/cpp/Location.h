#ifndef PROJECT_LOCATION_H
#define PROJECT_LOCATION_H

struct LocationInfo {
    double distanceMeters;
    double initialBearingDegrees;
    double finalBearingDegrees;
};

class Location {

public:
    /**
     * Calculate the distance in meters, initial bearing in degrees and final bearing in degrees between two WGS-84 points
     *
     * Calculations based on http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf using the "Inverse Formula" (section 4)
     */
    static void calculateLocationInfo(struct LocationInfo &locationInfo,
                                      double startLat,
                                      double startLng,
                                      double endLat,
                                      double endLng);

};


#endif //PROJECT_LOCATION_H
