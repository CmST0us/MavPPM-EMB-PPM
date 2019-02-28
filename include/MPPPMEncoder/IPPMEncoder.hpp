//
// Created by eric3u on 19-2-28.
//

#pragma once

#include "NoCopyable.hpp"

namespace ppm {

class IPPMEncoder : public utils::NoCopyable {
public:
    virtual ~IPPMEncoder() = 0;
    virtual int maxChannelCount() const = 0;
    virtual void writeValue(int channel, int value) = 0;

    virtual int maxChannelValue() const = 0;
    virtual int minChannelValue() const = 0;
};


}