//
// Created by eric3u on 19-2-28.
//

#pragma once

#include "IPPMEncoder.hpp"

namespace ppm {

class FakePPMEncoder final : public IPPMEncoder {
public:
    FakePPMEncoder();
    virtual ~FakePPMEncoder();
    virtual bool setup() override;
    virtual int maxChannelCount() const override;
    virtual void writeValue(int channel, int value) override;
    virtual void writeValue(int channel[], int value[], int count) override;
    virtual int readValue(int channel) const override;

    virtual int maxChannelValue() const override;
    virtual int minChannelValue() const override;

};

}