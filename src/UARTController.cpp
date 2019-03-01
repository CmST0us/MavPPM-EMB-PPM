//
// Created by eric3u on 19-2-28.
//

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "UARTController.hpp"

using namespace ppm;

UARTController::UARTController(const char *device, const int bandrate) : _device{device},
                                                                         _bandrate{bandrate} {
    _fd = -1;
}

bool UARTController::open() {
    struct termios options ;
    speed_t myBaud ;
    int     status, fd ;

    switch (_bandrate)
    {
        case     50:	myBaud =     B50 ; break ;
        case     75:	myBaud =     B75 ; break ;
        case    110:	myBaud =    B110 ; break ;
        case    134:	myBaud =    B134 ; break ;
        case    150:	myBaud =    B150 ; break ;
        case    200:	myBaud =    B200 ; break ;
        case    300:	myBaud =    B300 ; break ;
        case    600:	myBaud =    B600 ; break ;
        case   1200:	myBaud =   B1200 ; break ;
        case   1800:	myBaud =   B1800 ; break ;
        case   2400:	myBaud =   B2400 ; break ;
        case   4800:	myBaud =   B4800 ; break ;
        case   9600:	myBaud =   B9600 ; break ;
        case  19200:	myBaud =  B19200 ; break ;
        case  38400:	myBaud =  B38400 ; break ;
        case  57600:	myBaud =  B57600 ; break ;
        case 115200:	myBaud = B115200 ; break ;
        case 230400:	myBaud = B230400 ; break ;

        default:
            return -2 ;
    }

    if ((fd = ::open(_device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) < 0)
        return false;

    fcntl (fd, F_SETFL, O_RDWR) ;

// Get and modify current options:

    tcgetattr(fd, &options) ;

    cfmakeraw   (&options) ;
    cfsetispeed (&options, myBaud) ;
    cfsetospeed (&options, myBaud) ;

    options.c_cflag |= (CLOCAL | CREAD) ;
    options.c_cflag &= ~PARENB ;
    options.c_cflag &= ~CSTOPB ;
    options.c_cflag &= ~CSIZE ;
    options.c_cflag |= CS8 ;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG) ;
    options.c_oflag &= ~OPOST ;

    options.c_cc [VMIN]  =   0 ;
    options.c_cc [VTIME] = 100 ;	// Ten seconds (100 deciseconds)

    tcsetattr(fd, TCSANOW | TCSAFLUSH, &options) ;

    ioctl(fd, TIOCMGET, &status);

    status |= TIOCM_DTR ;
    status |= TIOCM_RTS ;

    ioctl(fd, TIOCMSET, &status);

    _fd = fd;
    usleep(10000) ;	// 10mS
    return true;
}

void UARTController::close() {
    ::close(_fd);
    _fd = -1;
}

void UARTController::flush(UARTControllerFlushBufferType flushBufferType) {
    ::tcflush(_fd, (int)flushBufferType);
}

void UARTController::putChar(const unsigned char c) {
    ::write(_fd, &c, 1);
}

void UARTController::puts(const char *s) {
    ::write(_fd, s, strlen(s));
}

void UARTController::printf(const char *s, ...) {
    va_list argp;
    char buffer[1024] = {0};

    va_start(argp, s);
    vsnprintf(buffer, 1023, s, argp);
    va_end(argp);
    this->puts(buffer);
}

int UARTController::dataAvailable() const {
    int result;
    if (ioctl(_fd, FIONREAD, &result) < 0) {
        return -1;
    }

    return result;
}

unsigned char UARTController::getChar() {
    unsigned char x;
    if (::read(_fd, &x, 1) < 0) {
        return 0xFF;
    }
    return (unsigned char)(x & 0xFF);
}

std::shared_ptr<utils::Data> UARTController::read(const int len) {
    std::shared_ptr<utils::Data> buf = std::make_shared<utils::Data>(len);
    int readLen = ::read(_fd, buf->getDataAddress(), (size_t)len);
    if (readLen > 0) {
        buf->setDataSize(readLen);
        return buf;
    }
    return nullptr;
}

void UARTController::write(std::shared_ptr<utils::Data> data) {
    if (data == nullptr)
        return;
    ::write(_fd, data->getDataAddress(), (size_t)data->getDataSize());
}