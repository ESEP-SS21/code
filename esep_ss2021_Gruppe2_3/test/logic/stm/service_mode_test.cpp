#include <gtest/gtest.h>
#include <logic/stm/service_mode/service_mode_context.h>
#include <logic/stm/service_mode/service_mode_states.h>

#include "dispatcher/color.h"

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

    const Event StepDoneEvent = {EventType::EVNT_ACT_CTRL_T_RST_LED_ON};
    const Event AckEvent = {EventType::EVNT_CTRL_T_RST_PRS_SRT};
    const Event AfterAckEvent = {EventType::EVNT_ACT_CTRL_T_RST_LED_OFF};
};

TEST_F(testServiceMode, StartState) {
    test_start_state<StartState>();
    test_transition_to<Calibrate>({EventType::EVNT_SRV_STR},
                                  {{EventType::EVNT_SEN_HEIGHT_REQ, 0}});

    test_transition_to<Leds>({EventType::EVNT_SEN_HEIGHT_HE, 88},
                             {{EventType::EVNT_SEN_HEIGHT_REQ, 88},
                              StepDoneEvent,
                              {EventType::EVNT_ACT_CTRL_T_STR_LED_ON},
                              {EventType::EVNT_ACT_CTRL_T_RST_LED_ON},
                             });

    test_transition_to<Stoplight>(AckEvent,
                                  {AfterAckEvent,
                                   {EventType::EVNT_ACT_CTRL_T_STR_LED_OFF},
                                   {EventType::EVNT_ACT_CTRL_T_RST_LED_OFF},
                                   {EventType::EVNT_ACT_STPL_LED_ON, Color::ALL},
                                   StepDoneEvent,
                                  });
}

}
}
}
