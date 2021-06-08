#include <gtest/gtest.h>
#include <logic/stm/StmMetalDetection/metal_detection_state.h>
#include "logic/stm/StmMetalDetection/metal_detect_context.h"
#include "util/stm_test_client.h"

#include "util/stm_test_base.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::StmMetalDetection;
using namespace ::logic::datamodel;

INIT_STM_TEST(testMetalDetection, MetalDetectionContext, UnitType::PRIMARY)

TEST_F(testMetalDetection, BeginsInRightState) {
    ASSERT_STATE(MetalDetection);
}

TEST_F(testMetalDetection, MetalWasDetected) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc;
    data.get_height_switch_sec()->enter_workpiece(wrpc);
    test_transition_to<MetalDetection>( { EventType::EVNT_SEN_METAL_DTC});
    ASSERT_TRUE(data.get_height_switch_sec()->first_workpiece().is_metallic);
}

TEST_F(testMetalDetection, NoWrpcsInSection) {
    data._operating_mode = OperatingMode::RUNNING;
    test_transition_to<MetalDetection>( { EventType::EVNT_SEN_METAL_DTC});
}

TEST_F(testMetalDetection, NotInRunning) {
    Workpiece wrpc;
    data.get_height_switch_sec()->enter_workpiece(wrpc);
    for (auto mode : OperatingModesNotRunning) {
        data._operating_mode = mode;
        test_transition_to<MetalDetection>({EventType::EVNT_SEN_METAL_DTC});
        ASSERT_FALSE(data.get_height_switch_sec()->first_workpiece().is_metallic);
    }
}

}
}
}

