#include <memory>
#include "workpiece.h"

namespace logic {
namespace datamodel {

id Workpiece::_last_id = 0;

Workpiece::Workpiece() :
        _id(_last_id) {
    _last_id = (_last_id + 1) % (max_id);
}

Workpiece::Workpiece(EncodedWorkpiece encoded_wrpc) :
        _id(encoded_wrpc.get_id()),
        type(encoded_wrpc.get_type()),
        height_1(encoded_wrpc.get_height_1()){
}

WorkpieceType Workpiece::get_type() const{
    return type;
}


EncodedWorkpiece Workpiece::encode() const {
    return EncodedWorkpiece(this->_id | (height_1 << 21) | ((int) type << 30));
}

id Workpiece::get_id() const{
    return _id;
}

void Workpiece::determine_type() {
    if (height_is_within_tolerance(height_bohrung, height_1)) {
        this->type = is_metallic ? WorkpieceType::WRPC_HM : WorkpieceType::WRPC_HB;
        return;
    }
    this->type =
            height_is_within_tolerance(height_low, height_1) ? WorkpieceType::WRPC_L :
            height_is_within_tolerance(height_high, height_1) ?
                    WorkpieceType::WRPC_H : WorkpieceType::Unknown;
}

} /* namespace datamodel */
} /* namespace logic*/

