//
// Created by eric3u on 19-2-28.
//

#pragma once

#include <string>
#include <memory>
#include "NoCopyable.hpp"
#include "Data.hpp"
namespace ppm {

enum class UARTControllerFlushBufferType {
    Input = 0,
    Output = 1,
    Both = 2,
};

class UARTController final : public utils::NoCopyable {
private:
    const std::string _device;
    const int _bandrate;
    int _fd;

public:
    UARTController(const char *device, const int bandrate);
    virtual ~UARTController();

    bool open();
    void close();
    void flush(UARTControllerFlushBufferType flushType = UARTControllerFlushBufferType::Both);
    void putChar(const unsigned char c);
    void puts(const char *s);
    void printf(const char *s, ...);
    void write(std::shared_ptr<utils::Data> data);
    unsigned char getChar();
    std::shared_ptr<utils::Data> read(const int len);
    int dataAvailable() const;

    int getFd() const;
};


}