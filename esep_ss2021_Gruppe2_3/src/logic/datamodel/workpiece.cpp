#include <memory>
#include "workpiece.h"

namespace logic {
namespace datamodel {

id Workpiece::_last_id = 0;

Workpiece::Workpiece() :
        wrpc_id(_last_id) {
    _last_id = (_last_id + 1) % (max_id);
}

Workpiece::Workpiece(EncodedWorkpiece& encoded_wrpc) {
    wrpc_id = encoded_wrpc.get_id();
    height_1 = encoded_wrpc.get_height();
    type = encoded_wrpc.get_type();
}

std::shared_ptr<EncodedWorkpiece> Workpiece::encode() const {
    return std::make_shared<EncodedWorkpiece>(this->wrpc_id | (height_1 << 21) | ((int) type << 30));
}

void Workpiece::determine_workpiece_type() {
    if (height_is_within_tolerance(height_bohrung, height_1)) {
        this->type = is_metallic ? WorkpieceType::WRPC_HM : WorkpieceType::WRPC_HB;
        return;
    }
    this->type =
            height_is_within_tolerance(height_low, height_1) ? WorkpieceType::WRPC_L :
            height_is_within_tolerance(height_high, height_1) ? WorkpieceType::WRPC_H :
                    WorkpieceType::unknown;
}

} /* namespace datamodel */
} /* namespace logic*/

