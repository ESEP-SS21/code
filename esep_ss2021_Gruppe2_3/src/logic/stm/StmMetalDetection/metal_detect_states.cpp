#include <logic/stm/StmMetalDetection/metal_detection_state.h>

namespace logic {
namespace stm {
namespace StmMetalDetection {

STATE_INIT(MetalDetection)

bool MetalDetection::metal_dtc() {
    auto wrpc = _datamodel->get_start_height_sec()->first_workpiece();
    wrpc.is_metallic = true;
    return true;
}



} /* namespace StmMetalDetection */
} /* namespace stm */
} /* namespace logic */
