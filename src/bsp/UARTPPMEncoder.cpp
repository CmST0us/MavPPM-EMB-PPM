//
// Created by eric3u on 19-2-28.
//

#include "UARTPPMEncoder.hpp"

using namespace ppm;

int UARTPPMEncoder::MAX_CHANNEL_COUNT = kUARTPPMEncoderMaxChannelCount;
int UARTPPMEncoder::MAX_CHANNEL_VALUE = kUARTPPMEncoderMaxChannelValue;
int UARTPPMEncoder::MIN_CHANNEL_VALUE = kUARTPPMEncoderMinChannelValue;

UARTPPMEncoder::UARTPPMEncoder(const char *device, int bandrate) {
    _uartController = std::make_shared<UARTController>(device, bandrate);
    for (int i = 0; i < UARTPPMEncoder::MAX_CHANNEL_COUNT; ++i) {
        _channelValue[i] = UARTPPMEncoder::MIN_CHANNEL_VALUE;
    }
}

UARTPPMEncoder::~UARTPPMEncoder() {
    _uartController->close();
}

bool UARTPPMEncoder::setup() {
    int ret = _uartController->open();
    if (!ret) {
        return false;
    }
}

int UARTPPMEncoder::maxChannelCount() const {
    return UARTPPMEncoder::MAX_CHANNEL_COUNT;
}

void UARTPPMEncoder::writeValue(int channel, int value) {
    if (channel >= maxChannelCount() ||
        channel < 0) {
        return;
    }

    if (value > maxChannelValue()) {
        value = maxChannelValue();
    } else if (value < minChannelValue()){
        value = minChannelValue();
    }

    _channelValue[channel] = value;

    // start code
    _uartController->putChar(0x0F);
    // data
    for(int i = 0; i < UARTPPMEncoder::MAX_CHANNEL_COUNT; ++i) {
    // (v - 400): UART to PPM IC FIX
        _uartController->putChar((_channelValue[i] - 400) / 10);
    }
    //end code
    _uartController->putChar(0x00);
}

int UARTPPMEncoder::readValue(int channel) const {
    if (channel >= maxChannelCount() ||
        channel < 0) {
        return -1;
    }

    return _channelValue[channel];
}

int UARTPPMEncoder::minChannelValue() const {
    return UARTPPMEncoder::MIN_CHANNEL_VALUE;
}

int UARTPPMEncoder::maxChannelValue() const {
    return UARTPPMEncoder::MAX_CHANNEL_VALUE;
}
