//
// Created by eric3u on 19-2-28.
//

#include "FakePPMEncoder.hpp"

using namespace ppm;


FakePPMEncoder::FakePPMEncoder() {

}

FakePPMEncoder::~FakePPMEncoder() {

}

bool FakePPMEncoder::setup() {
    return false;
}

int FakePPMEncoder::maxChannelCount() const {
    return 0;
}

void FakePPMEncoder::writeValue(int channel, int value) {

}

int FakePPMEncoder::readValue(int channel) const {
    return 0;
}

int FakePPMEncoder::minChannelValue() const {
    return 0;
}

int FakePPMEncoder::maxChannelValue() const {
    return 0;
}