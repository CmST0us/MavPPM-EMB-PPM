//
// Created by CmST0us on 2019/3/10.
//

#include "PPMEncoderFactory.hpp"
#include "FakePPMEncoder.hpp"
#include "UARTPPMEncoder.hpp"

std::shared_ptr<ppm::IPPMEncoder> ppm::PPMEncoderFactory::createPPMEncoder(ppm::SystemType systemType, const char *device, int bandrate) {
    switch (systemType) {
        case ppm::SystemType::PC_Unix_Like: {

        }
            break;

        case ppm::SystemType::EMB_NanoPi: {
            auto encoder = std::make_shared<ppm::UARTPPMEncoder>(device, bandrate);
            return encoder;
        }
            break;
        case ppm::SystemType::EMB_Common: {

        }
            break;
    }
    return nullptr;

}