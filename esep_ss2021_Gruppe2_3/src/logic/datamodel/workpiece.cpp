/*
 * workpiece.cpp
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

#include <memory>
#include "workpiece.h"

namespace logic {
namespace datamodel {

id Workpiece::_last_id = 0;

Workpiece::Workpiece() : wrpc_id(_last_id) {
    static constexpr int max_id_in_bits = 21;
    _last_id = _last_id % ((1 << max_id_in_bits) + 1);
}

Workpiece::Workpiece(EncodedWorkpiece& encoded_wrpc) {
    wrpc_id = encoded_wrpc.get_id();
    height_1 = encoded_wrpc.get_height();
    type = encoded_wrpc.get_type();
}

std::shared_ptr<EncodedWorkpiece> Workpiece::encode() const {
    return std::make_shared<EncodedWorkpiece>(this->wrpc_id | (height_1 << 21) | ((int)type << 30));
}

void Workpiece::determine_workpiece_type() {
    this->type = IS_LOW(height_1) ? WorkpieceType::WRPC_L :
                 IS_HIGH(height_1) ? WorkpieceType::WRPC_H :
                 HAS_BOHRUNG(height_1) ? (is_metallic ? WorkpieceType::WRPC_HM : WorkpieceType::WRPC_HB) :
                 WorkpieceType::unknown;
}

} /* namespace datamodel */
} /* namespace logic*/

