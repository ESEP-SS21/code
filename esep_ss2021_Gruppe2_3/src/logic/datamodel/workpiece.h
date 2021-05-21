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
    WorkpieceType type = WorkpieceType::unknown;
    const id wrpc_id = 0;
    float height_1;
    float height_2;
    bool is_metallic;
    bool is_flipped;

    Workpiece();
    Workpiece(EncodedWorkpiece);
    virtual ~Workpiece ();

    EncodedWorkpiece encode();
    void determine_workpiece_type();

private:
    id _last_id;
};

} /* namespace datamodel */
} /* namespace logic*/

#endif /* SRC_LOGIC_DATAMODEL_WORKPIECE_H_ */
