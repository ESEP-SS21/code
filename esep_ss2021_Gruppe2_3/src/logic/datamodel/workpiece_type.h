/*
 * workpiece_type.h
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

#ifndef SRC_LOGIC_DATAMODEL_WORKPIECE_TYPE_H_
#define SRC_LOGIC_DATAMODEL_WORKPIECE_TYPE_H_

namespace logic {
namespace datamodel {

enum class WorkpieceType {
    WRPC_H = 0, WRPC_HB, WRPC_HM, WRPC_L, unknown
};

} /* namespace datamodel */
} /* namespace logic*/

#endif /* SRC_LOGIC_DATAMODEL_WORKPIECE_TYPE_H_ */
