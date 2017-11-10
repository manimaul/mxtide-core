//
// Created by Willard Kamp on 11/9/17.
//

#include "LibXtide.h"

LibXtide::LibXtide() {
    stationIndex = std::make_unique<libxtide::StationIndex>();
}

void LibXtide::addHarmonicsFile(std::string harmonicsFile) {
    stationIndex->addHarmonicsFile(harmonicsFile.c_str());
}

size_t LibXtide::stationCount() {
    return stationIndex->size();
}

vector<string> LibXtide::stationList() {

    return vector<string>();
}

void LibXtide::setUnits(Unit unit) {
    this->unit = unit;
}
