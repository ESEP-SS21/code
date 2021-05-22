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

Workpiece::Workpiece() : wprc_id(_last_id) {
    if(_last_id >= 0x1fffff) {
        _last_id = 0;
    } else {
        _last_id++;
    }
}

Workpiece::Workpiece(EncodedWorkpiece& encoded_wrpc, int encoded_id) : wprc_id(encoded_id) {
    height_1 = encoded_wrpc.get_height();
    type = encoded_wrpc.get_type();
}

std::shared_ptr<EncodedWorkpiece> Workpiece::encode() const {
    return std::make_shared<EncodedWorkpiece>(this->wprc_id | (height_1 << 21) | ((int)type << 30));
}

void Workpiece::determine_workpiece_type() {
    if(HAS_BOHRUNG(height_1)) {
        if(this->is_metallic) {
            this->type = WorkpieceType::WRPC_HM;
        } else {
            this->type = WorkpieceType::WRPC_HB;
        }
    } else if(IS_LOW(height_1)) {
        this->type = WorkpieceType::WRPC_L;
    } else if(IS_HIGH(height_1)) {
        this->type = WorkpieceType::WRPC_H;
    } else {
        this->type = WorkpieceType::unknown;
    }
}

} /* namespace datamodel */
} /* namespace logic*/

