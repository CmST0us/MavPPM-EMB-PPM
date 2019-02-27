cmake_minimum_required(VERSION 3.0)

link_directories(../vendor/build/lib)

# Target

add_executable(
    test_ppm
    test_ppm.cpp
)

target_include_directories(test_ppm PRIVATE
    ../vendor/build/include
)
