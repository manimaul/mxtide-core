cmake_minimum_required(VERSION 3.4.1)

if (NOT ANDROID)
    set(CMAKE_CXX_STANDARD 17)
endif ()

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
        src/main/cpp/Location.h
        src/main/cpp/Optional.h
        )

set(LINK_LIBS mxtide xtide)

if (ANDROID)
    find_library(log-lib log)
    set(SOURCE_SET ${SOURCE_SET}
            src/main/cpp/jni/Jni.cpp
            src/main/cpp/jni/Jni.h
            src/main/cpp/jni/JniArrayList.cpp
            src/main/cpp/jni/JniArrayList.h
            src/main/cpp/jni/JniStation.cpp
            src/main/cpp/jni/JniStation.h
            src/main/cpp/jni/JniString.h
            src/main/cpp/jni/JniString.cpp
            src/main/cpp/jni/JniTidesAndCurrents.cpp
            src/main/cpp/jni/JniTidesAndCurrents.h
            src/main/cpp/jni/JniStationPrediction.h
            src/main/cpp/jni/JniStationPrediction.cpp
            )
    set(LINK_LIBS ${LINK_LIBS} ${log-lib})
    add_library(mxtide SHARED ${SOURCE_SET})
else ()
    set(SOURCE_SET ${SOURCE_SET}
            src/main/cpp/main.cpp
            src/main/cpp/PerfTimer.h
            )
    add_executable(mxtide ${SOURCE_SET})
endif ()


target_link_libraries(${LINK_LIBS})