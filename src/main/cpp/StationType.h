#pragma once

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
        bool equals(libxtide::StationRef* ref) {
            return (ref->isCurrent && type == current) || (!ref->isCurrent && type == tide);
        }
    };

    static const StationType stationTypeTide = StationType { StationType::Type::tide };
    static const StationType stationTypeCurrent = StationType { StationType::Type::current };
}
