cmake_minimum_required(VERSION 3.4.1)

if (NOT ANDROID)
    set(CMAKE_CXX_STANDARD 17)
endif ()

set(LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp/lib/)

set(xtide_DIR ${LIB_DIR})
find_package(xtide REQUIRED)

include_directories(src/main/cpp/include)

file(GLOB SOURCE_SET
        "src/main/cpp/*.cpp"
        "src/main/cpp/*.h"
        "src/main/cpp/include/*.h"
        )

set(LINK_LIBS mxtide xtide)

if (ANDROID)
    add_library(mxtide STATIC ${SOURCE_SET})
    target_include_directories(mxtide PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/include)
else ()
    set(SOURCE_SET ${SOURCE_SET}
            src/main/cpp/main.cpp
            src/main/cpp/PerfTimer.h
            )
    add_executable(mxtide ${SOURCE_SET})
endif ()

target_link_libraries(${LINK_LIBS})
