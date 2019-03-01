cmake_minimum_required(VERSION 3.0)

link_directories(../vendor/build/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

# Target
## test ppm
add_executable(
    test_ppm
    test_ppm.cpp
)

target_include_directories(test_ppm PRIVATE
    ../vendor/build/include
)

target_link_libraries(
    test_ppm PRIVATE
    wiringPi
    pthread
)

## test uart ppm
add_executable(
    test_uart_ppm
    test_uart_ppm.cpp
    ../src/UARTController.cpp
    ../src/bsp/UARTPPMEncoder.cpp
)

target_include_directories(
    test_uart_ppm
    PRIVATE
    ../include/MPPPMEncoder

)

target_link_libraries(
    test_uart_ppm
    PRIVATE
    pthread
)

