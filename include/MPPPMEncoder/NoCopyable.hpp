//
// Created by CmST0us on 2019/2/27.
//

#pragma once

namespace ppm {
namespace utils {
class NoCopyable {
protected:
    NoCopyable() {};

    ~NoCopyable() {};
private:
    NoCopyable(const NoCopyable &);

    const NoCopyable &operator=(const NoCopyable &);
};
}
}
