#include <logic/stm/StmMetalDetection/metal_detection_state.h>

namespace logic {
namespace stm {
namespace StmMetalDetection {

STATE_INIT(MetalDetection)

bool MetalDetection::metal_dtc() {

    auto section = _datamodel->get_start_height_sec();
    if (section->empty()) {
        std::cout << name << " Detected metal but there was no workpiece in the section" << std::endl;
        return true;
    }
    section->first_workpiece().is_metallic = true;
    return true;
}



} /* namespace StmMetalDetection */
} /* namespace stm */
} /* namespace logic */
