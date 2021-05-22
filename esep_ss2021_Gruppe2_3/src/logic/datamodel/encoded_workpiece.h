/*
 * encoded_workpiece.h
 *
 *  Created on: 21.05.2021
 *      Author: justi
 */

#ifndef SRC_LOGIC_DATAMODEL_ENCODED_WORKPIECE_H_
#define SRC_LOGIC_DATAMODEL_ENCODED_WORKPIECE_H_

#include <cstdint>
#include "workpiece_type.h"

static constexpr uint32_t ID_MASK = 0x1fffff;
static constexpr uint32_t HEIGHT_MASK = 0x3fe00000;
static constexpr uint32_t TYPE_MASK = 0xc0000000;

namespace logic {
namespace datamodel {

using id = uint32_t;

class EncodedWorkpiece {
public:
    const uint32_t code;

    EncodedWorkpiece(uint32_t code);

    id get_id();
    float get_height();
    WorkpieceType get_type();
};

} /* namespace datamodel */
} /* namespace logic*/

#endif /* SRC_LOGIC_DATAMODEL_ENCODED_WORKPIECE_H_ */
