//
// Created by Willard Kamp on 11/9/17.
//

#include <iostream>
#include "LibXtide.h"

int main() {
    std::string path = "/Users/willard/source/madrona/AndXtideLib/mxtide/src/main/res/raw/harmonics_dwf_20161231_free_tcd";
    auto xtide = LibXtide();
    xtide.addHarmonicsFile(path);
    std::cout << "station count:" << xtide.stationCount() << std::endl;
    return 0;
}