#include <gtest/gtest.h>
#include <logic/stm/StmOperationManager/operation_manager_states.h>
#include <logic/stm/StmOperationManager/operation_manager_context.h>
#include "util/stm_test_client.h"
#include "hal/hal.h"
#include "util/stm_test_base.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::operationManagerStm;

class testOperationManager : public stm_test_base<OperationManagerContext, ::logic::datamodel::UnitType::PRIMARY> {
public:
    void switch_to_running(){
        test_start_state<Idle>({
            {EventType::EVNT_ACT_STPL_LED_ON,::hal::Color::YELLOW},
            {EventType::EVNT_ACT_CTRL_T_STR_LED_ON}
        });
        test_transition_to<Running>({EventType::EVNT_CTRL_T_STR_PRS_SRT},
                {
                        {EventType::EVNT_ACT_STPL_LED_OFF,::hal::Color::YELLOW},
                        {EventType::EVNT_ACT_CTRL_T_STR_LED_OFF},
                        {EventType::EVNT_RST_TO_SRT},
                        {EventType::EVNT_ACT_STPL_LED_ON, ::hal::Color::GREEN},

                });
        ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::RUNNING);
    }
};

TEST_F(testOperationManager, BeginsInRightState){
    test_start_state<Idle>({
        {EventType::EVNT_ACT_STPL_LED_ON,::hal::Color::YELLOW},
        {EventType::EVNT_ACT_CTRL_T_STR_LED_ON}
    });
}

//############################################################//

TEST_F(testOperationManager, WarningsToErrorWithResolve) {
    switch_to_running();
    test_transition_to<Running>({EventType::EVNT_WRN},
            {
                    {EventType::EVNT_ACT_STPL_LED_BLNK_SLW,::hal::Color::YELLOW},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::RUNNING);
    ASSERT_EQ(data._warning_count , 1);

    test_transition_to<GoneUnacknowledged>({EventType::EVNT_CTRL_T_STP_PRS_SRT},
            {
                    {EventType::EVNT_ACT_BELT_STP},
                    {EventType::EVNT_ACT_SORT_RST},
                    {EventType::EVNT_ACT_STPL_LED_OFF, ::hal::Color::GREEN},
                    {EventType::EVNT_ACT_STPL_LED_BLNK_SLW,::hal::Color::RED},
                    {EventType::EVNT_ACT_CTRL_T_RST_LED_ON},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ERROR);

    test_transition_to<OK>({EventType::EVNT_CTRL_T_RST_PRS_SRT},
            {
                    {EventType::EVNT_ACT_CTRL_T_RST_LED_OFF},
                    {EventType::EVNT_ACT_STPL_LED_OFF,::hal::Color::RED},
                    {EventType::EVNT_ACT_CTRL_T_STR_LED_ON},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ERROR);

    test_transition_to<Running>({EventType::EVNT_CTRL_T_STR_PRS_SRT},
            {
                    {EventType::EVNT_ACT_CTRL_T_STR_LED_OFF},
                    {EventType::EVNT_HIST},
                    {EventType::EVNT_ACT_STPL_LED_ON, ::hal::Color::GREEN},

            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::RUNNING);
}

//############################################################//

TEST_F(testOperationManager, Service) {
    test_start_state<Idle>({
        {EventType::EVNT_ACT_STPL_LED_ON,::hal::Color::YELLOW},
        {EventType::EVNT_ACT_CTRL_T_STR_LED_ON}
    });
    test_transition_to<Service>({EventType::EVNT_CTRL_T_STR_PRS_LNG},
            {
                    {EventType::EVNT_ACT_STPL_LED_OFF,::hal::Color::YELLOW},
                    {EventType::EVNT_ACT_CTRL_T_STR_LED_OFF},
                    {EventType::EVNT_ACT_STPL_LED_BLNK_SLW,::hal::Color::GREEN}

            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::SERVICE);

    test_transition_to<Idle>({EventType::EVNT_SRV_DONE},
            {
                    {EventType::EVNT_ACT_STPL_LED_ON,::hal::Color::YELLOW},
                    {EventType::EVNT_ACT_CTRL_T_STR_LED_ON},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::IDLE);
}

//############################################################//

TEST_F(testOperationManager, WarningsBackToIdle) {
    switch_to_running();

    test_transition_to<Running>({EventType::EVNT_WRN},
            {
                    {EventType::EVNT_ACT_STPL_LED_BLNK_SLW,::hal::Color::YELLOW},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::RUNNING);
    ASSERT_EQ(data._warning_count , 1);

    test_transition_to<Running>({EventType::EVNT_WRN_GONE},
            {
                    {EventType::EVNT_ACT_STPL_LED_ON,::hal::Color::GREEN},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::RUNNING);
    ASSERT_EQ(data._warning_count , 0);

    test_transition_to<Idle>({EventType::EVNT_CTRL_T_STP_PRS_SRT},
            {
                    {EventType::EVNT_ACT_BELT_STP},
                    {EventType::EVNT_ACT_SORT_RST},
                    {EventType::EVNT_ACT_STPL_LED_OFF, ::hal::Color::GREEN},
                    {EventType::EVNT_ACT_STPL_LED_ON,::hal::Color::YELLOW},
                    {EventType::EVNT_ACT_CTRL_T_STR_LED_ON},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::IDLE);
}

//############################################################//

TEST_F(testOperationManager, Errors) {
    switch_to_running();

    test_transition_to<PendingUnacknowledged>({EventType::EVNT_ERR},
            {
                    {EventType::EVNT_ACT_BELT_STP},
                    {EventType::EVNT_ACT_SORT_RST},
                    {EventType::EVNT_ACT_STPL_LED_OFF, ::hal::Color::GREEN},
                    {EventType::EVNT_ACT_CTRL_T_RST_LED_ON},
                    {EventType::EVNT_ACT_STPL_LED_BLNK_FST, ::hal::Color::RED}
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ERROR);

    test_transition_to<PendingAcknowledged>({EventType::EVNT_CTRL_T_RST_PRS_SRT},
            {
                    {EventType::EVNT_ACT_CTRL_T_RST_LED_OFF},
                    {EventType::EVNT_ACT_STPL_LED_ON, ::hal::Color::RED},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ERROR);

    test_transition_to<OK>({EventType::EVNT_ERR_GONE},
            {
                    {EventType::EVNT_ACT_STPL_LED_OFF,::hal::Color::RED},
                    {EventType::EVNT_ACT_CTRL_T_STR_LED_ON},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ERROR);
}

//############################################################//

TEST_F(testOperationManager, ErrorGoneInPendingUnack) {
    switch_to_running();

    test_transition_to<PendingUnacknowledged>({EventType::EVNT_ERR},
            {
                    {EventType::EVNT_ACT_BELT_STP},
                    {EventType::EVNT_ACT_SORT_RST},
                    {EventType::EVNT_ACT_STPL_LED_OFF, ::hal::Color::GREEN},
                    {EventType::EVNT_ACT_CTRL_T_RST_LED_ON},
                    {EventType::EVNT_ACT_STPL_LED_BLNK_FST, ::hal::Color::RED}
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ERROR);

    test_transition_to<GoneUnacknowledged>({EventType::EVNT_ERR_GONE},
            {
                    {EventType::EVNT_ACT_STPL_LED_BLNK_SLW, ::hal::Color::RED},
                    {EventType::EVNT_ACT_CTRL_T_RST_LED_ON},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ERROR);
}

TEST_F(testOperationManager, EStop) {
    test_start_state<Idle>({
        {EventType::EVNT_ACT_STPL_LED_ON,::hal::Color::YELLOW},
        {EventType::EVNT_ACT_CTRL_T_STR_LED_ON}
    });
    test_transition_to<EStop>({EventType::EVNT_SEN_ESTOP_ON},
            {
                    {EventType::EVNT_ACT_STPL_LED_OFF,::hal::Color::YELLOW},
                    {EventType::EVNT_ACT_CTRL_T_STR_LED_OFF},
                    {EventType::EVNT_ACT_STPL_LED_BLNK_SLW,::hal::Color::RED},
                    {EventType::EVNT_ACT_CTRL_T_RST_LED_ON},

            });
    ASSERT_EQ(data._estop_count,1);
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ESTOP);

    test_transition_to<EStop>({EventType::EVNT_SEN_ESTOP_ON},{});
    ASSERT_EQ(data._estop_count,2);
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ESTOP);

    test_transition_to<EStop>({EventType::EVNT_SEN_ESTOP_OFF},{});
    ASSERT_EQ(data._estop_count,1);
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ESTOP);

    test_transition_to<EStop>({EventType::EVNT_SEN_ESTOP_OFF},{});
    ASSERT_EQ(data._estop_count,0);
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::ESTOP);

    test_transition_to<Idle>({EventType::EVNT_CTRL_T_RST_PRS_SRT},
            {
                    {EventType::EVNT_ACT_STPL_LED_OFF, ::hal::Color::RED},
                    {EventType::EVNT_ACT_CTRL_T_RST_LED_OFF},
                    {EventType::EVNT_ACT_STPL_LED_ON,::hal::Color::YELLOW},
                    {EventType::EVNT_ACT_CTRL_T_STR_LED_ON},
            });
    ASSERT_EQ(data._operating_mode , ::logic::datamodel::OperatingMode::IDLE);
}

}
}
}



