//
// Created by eric3u on 19-2-28.
//

#include "FakePPMEncoder.hpp"

using namespace ppm;


FakePPMEncoderr::FakePPMEncoderr() {

}

FakePPMEncoderr::~FakePPMEncoderr() {

}

int FakePPMEncoderr::maxChannelCount() const {
    return 0;
}

void FakePPMEncoderr::writeValue(int channel, int value) {

}

int FakePPMEncoderr::minChannelValue() const {
    return 0;
}

int FakePPMEncoderr::maxChannelValue() const {
    return 0;
}