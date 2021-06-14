#include <logic/stm/StmMetalDetection/metal_detection_state.h>

namespace logic {
namespace stm {
namespace StmMetalDetection {

STATE_INIT(MetalDetection)

bool MetalDetection::metal_dtc() {

    auto hs_section = _datamodel->get_height_switch_sec();
    if (hs_section->workpiece_count() == 0) {
        _logger->error("{} Detected metal but there was no workpiece in the section", name);
        return true;
    }
    hs_section->first_workpiece().is_metallic = true;
    hs_section->first_workpiece().determine_type();
    return true;
}



} /* namespace StmMetalDetection */
} /* namespace stm */
} /* namespace logic */
