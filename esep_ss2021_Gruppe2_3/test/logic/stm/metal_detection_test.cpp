#include <gtest/gtest.h>
#include <logic/stm/StmMetalDetection/metal_detection_state.h>
#include "logic/stm/StmMetalDetection/metal_detect_context.h"
#include "util/stm_test_client.h"

#include "util/stm_test_base.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::StmMetalDetection;

INIT_STM_TEST(testMetalDetection, MetalDetectionContext,
        ::logic::datamodel::UnitType::PRIMARY)

TEST_F(testMetalDetection, BeginsInRightState) {
    ASSERT_STATE(MetalDetection);
}

TEST_F(testMetalDetection, MetalWasDetected) {
    ::logic::datamodel::Workpiece wrpc;
    data.get_start_height_sec()->enter_workpiece(wrpc);
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    test_transition_to<MetalDetection>( { EventType::EVNT_SEN_METAL_DTC});
    ASSERT_EQ(data.get_start_height_sec()->first_workpiece().is_metallic, true);
}


}
}
}

