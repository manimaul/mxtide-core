#ifndef PROJECT_UNIT_H
#define PROJECT_UNIT_H

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

#endif //PROJECT_UNIT_H
