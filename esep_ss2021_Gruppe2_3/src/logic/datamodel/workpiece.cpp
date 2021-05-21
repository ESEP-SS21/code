/*
 * workpiece.cpp
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

#include "workpiece.h"

namespace logic {
namespace datamodel {

Workpiece::Workpiece(id wprc_id) : wprc_id(wprc_id) {
    is_metallic = false;
    is_flipped = false;
}

Workpiece::Workpiece(EncodedWorkpiece encoded_wrpc) {

}

Workpiece::~Workpiece () {

}

EncodedWorkpiece Workpiece::encode() {

}

void Workpiece::determine_workpiece_type() {

}

} /* namespace datamodel */
} /* namespace logic*/

