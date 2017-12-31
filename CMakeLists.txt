cmake_minimum_required(VERSION 3.4.1)

if (NOT ANDROID)
    set(CMAKE_CXX_STANDARD 17)
endif ()

set(LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp/lib/)

set(xtide_DIR ${LIB_DIR})
find_package(xtide REQUIRED)

set(SOURCE_SET
        src/main/cpp/Location.cpp
        src/main/cpp/Location.h
        src/main/cpp/MeasureUnit.h
        src/main/cpp/Optional.h
        src/main/cpp/Station.cpp
        src/main/cpp/Station.h
        src/main/cpp/StationPrediction.h
        src/main/cpp/StationType.h
        src/main/cpp/TidesAndCurrents.cpp
        src/main/cpp/TidesAndCurrents.h
        )

set(LINK_LIBS mxtide xtide)

if (ANDROID)
    add_library(mxtide STATIC ${SOURCE_SET})
    target_include_directories(mxtide PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/)
else ()
    set(SOURCE_SET ${SOURCE_SET}
            src/main/cpp/main.cpp
            src/main/cpp/PerfTimer.h
            )
    add_executable(mxtide ${SOURCE_SET})
endif ()

target_link_libraries(${LINK_LIBS})
