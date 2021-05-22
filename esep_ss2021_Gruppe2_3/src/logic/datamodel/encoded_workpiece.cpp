/*
 * encoded_workpiece.cpp
 *
 *  Created on: 21.05.2021
 *      Author: justi
 */

#include <logic/datamodel/encoded_workpiece.h>

namespace logic {
namespace datamodel {

EncodedWorkpiece::EncodedWorkpiece(uint32_t code) : code(code) {}

id EncodedWorkpiece::get_id() {
    return code & ID_MASK;
}

float EncodedWorkpiece::get_height() {
    return (code & HEIGHT_MASK) >> 21;
}

WorkpieceType EncodedWorkpiece::get_type() {
    return static_cast<WorkpieceType>((code & TYPE_MASK) >> 30);
}

} /* namespace datamodel */
} /* namespace logic*/
