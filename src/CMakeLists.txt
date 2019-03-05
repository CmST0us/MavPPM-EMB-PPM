cmake_minimum_required(VERSION 3.0)

# Options
option(BUILD_FOR_EMB "Build For EMB Device" OFF)
if (NOT DEFINED BUILD_FOR_EMB)
    set(BUILD_FOR_EMB OFF)
endif()

# Source
aux_source_directory(. mavppm_ppmencoder_source)


if (BUILD_FOR_EMB STREQUAL "ON")
    aux_source_directory(./bsp mavppm_ppmencoder_source_bsp)
endif()

link_directories(../vendor/build/lib)

# Target
add_library(
    MavPPM_PPMEncoder
    STATIC
    ${mavppm_ppmencoder_source}
    ${mavppm_ppmencoder_source_bsp}
)

target_include_directories(MavPPM_PPMEncoder PUBLIC
    ../include/MPPPMEncoder
)

target_include_directories(MavPPM_PPMEncoder PRIVATE
    .
    ./bsp
    ../vendor/build/include
)

# Install
## Install Target
install(
    TARGETS MavPPM_PPMEncoder
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

## Install Header
install(
    DIRECTORY
        ../include/MPPPMEncoder
    DESTINATION
        include
)