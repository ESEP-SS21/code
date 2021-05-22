/*
 * workpiece.cpp
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

#include "workpiece.h"

namespace logic {
namespace datamodel {

Workpiece::Workpiece(id wprc_id) : wprc_id(wprc_id) {}

Workpiece::Workpiece(EncodedWorkpiece encoded_wrpc) {
    //wrpc_id = encoded_wrpc.get_id();
    height_1 = encoded_wrpc.get_height();
    type = encoded_wrpc.get_type();
}

EncodedWorkpiece Workpiece::encode() {
    //return id | (height_1 << 21) | (type << 30);
}

void Workpiece::determine_workpiece_type() {

}

} /* namespace datamodel */
} /* namespace logic*/

