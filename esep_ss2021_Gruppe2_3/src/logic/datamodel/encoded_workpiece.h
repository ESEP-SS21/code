#pragma once

#include <cstdint>
#include "workpiece_type.h"

static constexpr uint32_t ID_MASK = 0x1fffff;       // first 21 bits
static constexpr uint32_t HEIGHT_MASK = 0x3fe00000; // 9 bits in between
static constexpr uint32_t TYPE_MASK = 0xc0000000;   // last 2 bits

namespace logic {
namespace datamodel {

using id = uint32_t;

class EncodedWorkpiece {
public:
    /**
     * Code besteht aus Informationen ueber das Werkstueck:
     * - 21-bit ID
     * - 9-bit Hoehe in Zehntel-Millimeter
     * - 2-bit Werkstueck-Typ
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

