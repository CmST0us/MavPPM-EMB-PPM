//
// Created by eric3u on 19-2-28.
//

#pragma once

#include "IPPMEncoder.hpp"

namespace ppm {

class FakePPMEncoderr final : public IPPMEncoder {
public:
    FakePPMEncoderr();
    virtual ~FakePPMEncoderr();
    virtual int maxChannelCount() const override;
    virtual void writeValue(int channel, int value) override;

    virtual int maxChannelValue() const override;
    virtual int minChannelValue() const override;

};

}