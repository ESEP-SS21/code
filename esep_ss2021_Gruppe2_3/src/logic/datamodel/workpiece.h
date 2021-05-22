/*
 * workpiece.h
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

#ifndef SRC_LOGIC_DATAMODEL_WORKPIECE_H_
#define SRC_LOGIC_DATAMODEL_WORKPIECE_H_

#include <cstdint>
#include "workpiece_type.h"
#include "encoded_workpiece.h"

namespace logic {
namespace datamodel {

using id = uint32_t;

class Workpiece {
public:
    const id wprc_id;

    WorkpieceType type = WorkpieceType::unknown;
    int height_1 = 0;
    int height_2 = 0;
    bool is_metallic = false;
    bool is_flipped = false;

    Workpiece();
    Workpiece(EncodedWorkpiece&, int encoded_id);

    EncodedWorkpiece& encode();
    void determine_workpiece_type();

private:
    static id _last_id;
};

} /* namespace datamodel */
} /* namespace logic*/

#endif /* SRC_LOGIC_DATAMODEL_WORKPIECE_H_ */
