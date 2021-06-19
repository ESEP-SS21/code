#include <gtest/gtest.h>
#include <logic/stm/service_mode/service_mode_context.h>
#include <logic/stm/service_mode/service_mode_states.h>

#include "util/stm_test_client.h"
#include "util/stm_test_base.h"
#include "../workpiece_helper.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::stm_service_mode;
using namespace ::logic::datamodel;

class testServiceMode : public stm_test_base<ServiceModeContext, ::logic::datamodel::UnitType::PRIMARY> {
public:
    testServiceMode() {
        data._operating_mode = ::logic::datamodel::OperatingMode::SERVICE;
    }
};

TEST_F(testServiceMode, StartState) {
    test_start_state<StartState>();
    test_transition_to<Calibrate>({EventType::EVNT_SRV_STR},
                                  {{EventType::EVNT_SEN_HEIGHT_REQ, 0}});
    test_transition_to<Stoplight>({EventType::EVNT_SEN_HEIGHT_HE, 88},
                                  {{EventType::EVNT_SEN_HEIGHT_REQ, 88},
                                   {EventType::EVNT_ACT_STPL_LED_ON, 4},
                                   {EventType::EVNT_ACT_CTRL_T_RST_LED_ON},
                                   });
}

//
//TEST_F(testReceiveWrpcStmPrimary, TransitionBeltNotBlockedPri) {
//    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
//    data._belt_blocked = false;
//    test_start_state<BeltNotRunning>({
//        {EventType::EVNT_ACT_BELT_STP}
//    });
//    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 0);
//    test_transition_to<BeltRunning>({EventType::EVNT_SEN_LB_ST_BLCK}, {EventType::EVNT_ACT_BELT_FWD});
//    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 1);
//
//}
//
//TEST_F(testReceiveWrpcStmPrimary, TransitionBeltBlockedPri) {
//    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
//    data._belt_blocked = true;
//    test_start_state<BeltNotRunning>({
//        {EventType::EVNT_ACT_BELT_STP}
//    });
//    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 0);
//    test_transition_to<BeltNotRunning>({EventType::EVNT_SEN_LB_ST_BLCK});
//    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 1);
//
//}

}
}
}
