#pragma once

#include <cstdint>
#include "workpiece_type.h"

namespace logic {
namespace datamodel {

static constexpr uint32_t ID_MASK = 0x001fffff;       // first 21 bits
static constexpr uint32_t HEIGHT_MASK = 0x01ff << 21 ; // 9 bits in between
static constexpr uint32_t TYPE_MASK = 0b11 << 30;   // last 2 bits

using id = uint32_t;

class EncodedWorkpiece {
public:
    /**
     * Consist of the following information:
     * - 21 bit: ID
     * -  9 bit: height in 0.1mm precision
     * -  2 bit: WorkpieceType
     */
    const uint32_t code;

    EncodedWorkpiece(uint32_t code);
    virtual ~EncodedWorkpiece() = default;

    id get_id() const;
    int get_height() const;
    WorkpieceType get_type() const;
};

} /* namespace datamodel */
} /* namespace logic*/

