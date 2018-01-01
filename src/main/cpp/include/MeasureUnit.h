#pragma once

namespace mdr {
    enum MeasureUnit {
        meters,
        feet
    };

    static MeasureUnit MeasureUnitFromString(std::string &str) {
        if (str == "feet") {
            return MeasureUnit::feet;
        } else {
            return MeasureUnit::meters;
        }
    }
}
