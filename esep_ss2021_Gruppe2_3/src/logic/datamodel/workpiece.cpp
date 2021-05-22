/*
 * workpiece.cpp
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

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

EncodedWorkpiece& Workpiece::encode() const {
    //return EncodedWorkpiece(id | (height_1 << 21) | (type << 30));
}

void Workpiece::determine_workpiece_type() {

}

} /* namespace datamodel */
} /* namespace logic*/

