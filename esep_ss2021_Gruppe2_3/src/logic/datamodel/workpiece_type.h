#pragma once

namespace logic {
namespace datamodel {

/*
 * All types above 'WRPC_H' are ordered by the desired sorting order.
 * All types including and below 'WRPC_H' are to be discarded.
 */
enum class WorkpieceType {
    WRPC_HM = 0, WRPC_HB, WRPC_L,
    //^^^ need to be in sorting order ^^^
    WRPC_H, // WRPC_H needs to be first in enum, which is to be discarded
    Unknown
};

} /* namespace datamodel */
} /* namespace logic*/
