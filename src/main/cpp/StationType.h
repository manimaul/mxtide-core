#ifndef PROJECT_STATIONTYPE_H
#define PROJECT_STATIONTYPE_H

#include <string>

namespace mdr {

    struct StationType {
        enum Type { tide, current, };
        Type type;
        std::string toString() {
            switch (type) {
                case current:
                    return "current";
                default:
                case tide:
                    return "tide";
            }
        }
    };

    static const StationType stationTypeTide = StationType { StationType::Type::tide };
    static const StationType stationTypeCurrent = StationType { StationType::Type::current };
}


#endif //PROJECT_STATIONTYPE_H