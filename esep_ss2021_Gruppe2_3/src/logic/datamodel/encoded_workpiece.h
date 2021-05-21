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

namespace logic {
namespace datamodel {

using id = uint32_t;

class EncodedWorkpiece {
public:
    const uint32_t code = 0;

    EncodedWorkpiece(uint32_t code);
    virtual ~EncodedWorkpiece();

    id get_id();
    float get_height();
    WorkpieceType get_type();
};

} /* namespace datamodel */
} /* namespace logic*/

#endif /* SRC_LOGIC_DATAMODEL_ENCODED_WORKPIECE_H_ */
