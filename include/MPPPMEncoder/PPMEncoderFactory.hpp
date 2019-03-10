//
// Created by CmST0us on 2019/3/10.
//

#pragma once

#include <memory>

#include "IPPMEncoder.hpp"
#include "NoCopyable.hpp"

namespace ppm {

enum class SystemType {
    PC_Unix_Like,

    EMB_NanoPi,
    EMB_Common,
};

class PPMEncoderFactory final : public ppm::utils::NoCopyable {
public:
    /*
     * 请使用次方法返回对应系统的PPM控制器
     * PC_Unix_Like: FakePPMEncoder
     * EMB_NanoPi: UARTPPMEncoder
     * EMB_Common: FakePPMEncoder
     *
     */
    static std::shared_ptr<ppm::IPPMEncoder> createPPMEncoder(ppm::SystemType systemType, const char *device = "/dev/ttyS1", int bandrate = 4800);

};

}