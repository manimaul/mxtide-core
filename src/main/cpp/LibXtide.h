//
// Created by Willard Kamp on 11/9/17.
//

#ifndef PROJECT_LIBXTIDE_H
#define PROJECT_LIBXTIDE_H

#include <string>
#include <xtide/libxtide.hh>
#include "Unit.h"

using namespace std;

class LibXtide {

private:
    unique_ptr<libxtide::StationIndex> stationIndex;
    Unit unit = Unit::meters;

public:
    LibXtide();
    void addHarmonicsFile(std::string harmonicsFile);
    size_t stationCount();
    vector<string> stationList();
    void setUnits(Unit unit);
};


#endif //PROJECT_LIBXTIDE_H
