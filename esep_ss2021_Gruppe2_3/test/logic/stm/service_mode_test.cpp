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

class testServiceMode : public stm_test_base<ServiceModeContext,
    ::logic::datamodel::UnitType::PRIMARY> {
public:
    testServiceMode() {
        data._operating_mode = ::logic::datamodel::OperatingMode::SERVICE;
    }

    const Event TurnOnLedsAfterStepDone = {EventType::EVNT_ACT_CTRL_T_RST_LED_ON};
    const Event AckStepDoneWithRst = {EventType::EVNT_CTRL_T_RST_PRS_SRT};
    const Event TurnOffLedsAfterAck = {EventType::EVNT_ACT_CTRL_T_RST_LED_OFF};
};

TEST_F(testServiceMode, StartState) {
    test_start_state<StartState>();

    test_transition_to<Calibrate>({EventType::EVNT_SRV_STR},
                                  {{EventType::EVNT_SEN_HEIGHT_REQ, 0}});

    test_transition_to<Leds>({EventType::EVNT_SEN_HEIGHT_HE, 88},
                             {{EventType::EVNT_SEN_HEIGHT_REQ, 88},
                              TurnOnLedsAfterStepDone,
                              {EventType::EVNT_ACT_CTRL_T_STR_LED_ON},
                              {EventType::EVNT_ACT_CTRL_T_RST_LED_ON},});

    test_transition_to<Stoplight>(AckStepDoneWithRst,
                                  {TurnOffLedsAfterAck,
                                   {EventType::EVNT_ACT_CTRL_T_STR_LED_OFF},
                                   {EventType::EVNT_ACT_CTRL_T_RST_LED_OFF},
                                   {EventType::EVNT_ACT_STPL_LED_ON, Color::ALL},
                                   TurnOnLedsAfterStepDone,});

    test_transition_to<BeltFwd>(AckStepDoneWithRst,
                                {TurnOffLedsAfterAck,
                                 {EventType::EVNT_ACT_STPL_LED_BLNK_SLW, Color::GREEN},
                                 {EventType::EVNT_ACT_BELT_FWD},
                                 TurnOnLedsAfterStepDone});

    test_transition_to<BeltBwd>(AckStepDoneWithRst,
                                {TurnOffLedsAfterAck,
                                 {EventType::EVNT_ACT_BELT_STP},
                                 {EventType::EVNT_ACT_BELT_BWD},
                                 TurnOnLedsAfterStepDone});

    test_transition_to<SortDisc>(AckStepDoneWithRst,
                                 {TurnOffLedsAfterAck,
                                  {EventType::EVNT_ACT_BELT_STP},
                                  {EventType::EVNT_ACT_SORT_DSC},
                                  Event::CreateTimer(TimerID::SRV_Timer, 2000)});

    test_transition_to<SortDisc>({EventType::EVNT_TIM_ALRT, static_cast<int>(TimerID::SRV_Timer)},
                                 {{EventType::EVNT_ACT_SORT_RST},
                                  TurnOnLedsAfterStepDone});

    test_transition_to<SortNoDisc>(AckStepDoneWithRst,
                                   {TurnOffLedsAfterAck,
                                    {EventType::EVNT_ACT_SORT_RST},
                                    {EventType::EVNT_ACT_SORT_NO_DSC},
                                    Event::CreateTimer(TimerID::SRV_Timer, 2000)});

    test_transition_to<SortNoDisc>({EventType::EVNT_TIM_ALRT, static_cast<int>(TimerID::SRV_Timer)},
                                   {{EventType::EVNT_ACT_SORT_RST},
                                    TurnOnLedsAfterStepDone});

    test_transition_to<Sensors>(AckStepDoneWithRst,
                                {TurnOffLedsAfterAck,
                                 {EventType::EVNT_ACT_SORT_RST}});

    for (Event event : {Event(EventType::EVNT_SEN_LB_ST_CLR),
                        Event(EventType::EVNT_SEN_LB_EN_CLR),
                        Event(EventType::EVNT_SEN_LB_SW_CLR),
                        Event(EventType::EVNT_SEN_LB_RA_CLR)}) {

        test_transition_to<Sensors>(event,
                                    {{EventType::EVNT_ACK}});

        test_transition_to<Sensors>({EventType::EVNT_ACK});

        test_transition_to<Sensors>({EventType::EVNT_ACK},
                                    {TurnOnLedsAfterStepDone});

        test_transition_to<Sensors>(AckStepDoneWithRst,
                                    {TurnOffLedsAfterAck});
    }


    test_transition_to<Sensors>({EventType::EVNT_SEN_METAL_DTC},
                                {{EventType::EVNT_ACK}});

    test_transition_to<Sensors>({EventType::EVNT_ACK});

    test_transition_to<Sensors>({EventType::EVNT_ACK},
                                {TurnOnLedsAfterStepDone});

    test_transition_to<StartState>(AckStepDoneWithRst,
                                   {TurnOffLedsAfterAck});
}

}
}
}
