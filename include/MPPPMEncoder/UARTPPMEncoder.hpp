//
// Created by eric3u on 19-2-28.
//
#pragma once

#include <memory>
#include <thread>
#include <functional>
#include <future>
#include "UARTController.hpp"
#include "IPPMEncoder.hpp"


#define kUARTPPMEncoderMaxChannelCount (8)
#define kUARTPPMEncoderMaxChannelValue (1900)
#define kUARTPPMEncoderMinChannelValue (1100)

namespace ppm {

class UARTPPMEncoder final : public IPPMEncoder {
public:
    static int MAX_CHANNEL_COUNT;
    static int MAX_CHANNEL_VALUE;
    static int MIN_CHANNEL_VALUE;

public:
    UARTPPMEncoder(const char *device, int bandrate);
    virtual ~UARTPPMEncoder() override;
    virtual bool setup() override;
    virtual int maxChannelCount() const override;
    virtual void writeValue(int channel, int value) override;
    virtual void writeValue(int channel[], int value[], int count) override;
    virtual int readValue(int channel) const override ;

    virtual int maxChannelValue() const override;
    virtual int minChannelValue() const override;

private:
    std::shared_ptr<UARTController> _uartController{nullptr};
    int _channelValue[kUARTPPMEncoderMaxChannelCount];

    void update();
};

}