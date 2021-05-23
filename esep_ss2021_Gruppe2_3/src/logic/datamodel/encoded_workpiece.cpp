#include <logic/datamodel/encoded_workpiece.h>

namespace logic {
namespace datamodel {

EncodedWorkpiece::EncodedWorkpiece(uint32_t code) :
        code(code) {
}

id EncodedWorkpiece::get_id() const {
    return code & ID_MASK;
}

int EncodedWorkpiece::get_height() const {
    return (code & HEIGHT_MASK) >> 21;
}

WorkpieceType EncodedWorkpiece::get_type() const {
    return static_cast<WorkpieceType>((code & TYPE_MASK) >> 30);
}

} /* namespace datamodel */
} /* namespace logic*/
