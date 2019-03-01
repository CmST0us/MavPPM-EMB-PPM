//
// Created by eric3u on 19-3-1.
//

#include "UARTController.hpp"
#include "UARTPPMEncoder.hpp"

int main(int argc, char *argv[]) {

    std::shared_ptr<ppm::UARTPPMEncoder> encoder = std::make_shared<ppm::UARTPPMEncoder>("/dev/ttyS1", 4800);
    encoder->setup();

    for (int i = 0; i < 9; ++i) {
        encoder->writeValue(1, 1100 + i * 100);
    }

    return 0;
}