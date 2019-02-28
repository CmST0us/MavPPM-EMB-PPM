//
// Created by eric3u on 19-2-28.
//
#pragma once

#include "IPPMEncoder.hpp"

namespace ppm {

class UARTPPMEncoder final : public IPPMEncoder {
public:
    UARTPPMEncoder();
    virtual ~UARTPPMEncoder();
    virtual int maxChannelCount() const override;
    virtual void writeValue(int channel, int value) override;

    virtual int maxChannelValue() const override;
    virtual int minChannelValue() const override;

};

}