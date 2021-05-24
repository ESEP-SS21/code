#pragma once

#include <cstdint>
#include "workpiece_type.h"

namespace logic {
namespace datamodel {

using id = uint32_t;

struct EncodedWorkpiece {
private:
    static constexpr uint32_t ID_MASK = 0x001fffff;       // first 21 bits
    static constexpr uint32_t HEIGHT_MASK = 0x01ff << 21; // 9 bits in between
    static constexpr uint32_t TYPE_MASK = 0b11 << 30;     // last 2 bits
public:
    /**
     * Consist of the following information:
     * - 21 bit: ID
     * -  9 bit: height in 0.1mm precision
     * -  2 bit: WorkpieceType
     */
    const uint32_t code;

    EncodedWorkpiece(uint32_t code) :
            code(code) {
    }

    virtual ~EncodedWorkpiece() = default;

    id get_id() const {
        return code & ID_MASK;
    }

    int get_height_1() const {
        return (code & HEIGHT_MASK) >> 21;
    }

    WorkpieceType get_type() const {
        return WorkpieceType((code & TYPE_MASK) >> 30);
    }
};

} /* namespace datamodel */
} /* namespace logic*/

