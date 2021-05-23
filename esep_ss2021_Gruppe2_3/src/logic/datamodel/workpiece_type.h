#pragma once

namespace logic {
namespace datamodel {

enum class WorkpieceType {
    WRPC_HM = 0, WRPC_HB, WRPC_H,
    WRPC_L, //needs to be first, which is not in sorting order
    Unknown
};

} /* namespace datamodel */
} /* namespace logic*/
