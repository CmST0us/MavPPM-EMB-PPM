//
// Created by CmST0us on 2019/2/27.
//

#pragma once

#include "NoCopyable.hpp"

namespace ppm {

class PPMEncoder final : public utils::NoCopyable {
public:
    PPMEncoder();
    virtual ~PPMEncoder();
};

}