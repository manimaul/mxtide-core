cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 17)

set(LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp/lib/)

set(xtide_DIR ${LIB_DIR})
find_package(xtide REQUIRED)

set(SOURCE_SET
        src/main/cpp/TidesAndCurrents.cpp
        src/main/cpp/TidesAndCurrents.h
        src/main/cpp/MeasureUnit.h
        src/main/cpp/Station.h
        src/main/cpp/Station.cpp
        src/main/cpp/StationType.h
        src/main/cpp/StationPrediction.h
        src/main/cpp/Location.cpp
        src/main/cpp/Location.h)

set(LINK_LIBS mxtide xtide)

if (ANDROID)
    find_library(log-lib log)
    set(SOURCE_SET ${SOURCE_SET}
            src/main/cpp/AndXTideLib.cpp
            src/main/cpp/AndXTideLib.hh
            )
    set(LINK_LIBS ${LINK_LIBS} ${log-lib})
    add_library(mxtide SHARED ${SOURCE_SET})
else ()
    set(SOURCE_SET ${SOURCE_SET}
            src/main/cpp/main.cpp
            )
    add_executable(mxtide ${SOURCE_SET})
endif ()


target_link_libraries(${LINK_LIBS})