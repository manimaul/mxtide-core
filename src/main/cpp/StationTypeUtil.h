#pragma once

#ifndef LIB_XTIDE_H
#define LIB_XTIDE_H

#include <xtide/libxtide.hh>

#endif

#include <StationType.h>

namespace mdr {

    static bool stationTypeEquals(StationType &type, libxtide::StationRef* ref) {
        return (ref->isCurrent && type.type == StationType::current) || (!ref->isCurrent && type.type == StationType::tide);
    }

}