#include <gtest/gtest.h>
#include <logic/stm/StmAnswerTransferReq/answer_transfer_req_states.h>
#include "logic/stm/StmAnswerTransferReq/answer_transfer_req_context.h"
#include "util/stm_test_client.h"

#include "util/stm_test_base.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::StmAnswerTransferReq;

INIT_STM_TEST(testAnswerTransferReq, AnswerTransferReqContext,
        ::logic::datamodel::UnitType::SECONDARY)

TEST_F(testAnswerTransferReq, BeginsInRightState) {
    ASSERT_STATE(Waiting);
}

TEST_F(testAnswerTransferReq, PendingIsSetRight) {
    ::logic::datamodel::Workpiece wrpc;
    wrpc.height_1 = ::logic::datamodel::Workpiece::height_low;
    wrpc.determine_type();
    auto encoded = wrpc.encode();
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    test_transition_to<Waiting>( { EventType::EVNT_WRPC_TRNS_RQ, encoded.code }, { {
            EventType::EVNT_ACK }, { EventType::EVNT_ACT_BELT_FWD } });
    auto recieved = *data.get_pending_transfer();
    ASSERT_EQ(wrpc, recieved);
}

TEST_F(testAnswerTransferReq, TransitionTree) {
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    test_transition_to<Waiting>( { EventType::EVNT_WRPC_TRNS_RQ }, { { EventType::EVNT_ACK }, {
            EventType::EVNT_ACT_BELT_FWD } });
    data._belt_blocked = true;
    test_transition_to<WaitingForSpace>( { EventType::EVNT_WRPC_TRNS_RQ }, { });
    test_transition_to<Waiting>( { EventType::EVNT_SEN_LB_HE_BLCK }, { { EventType::EVNT_ACK }, {
            EventType::EVNT_ACT_BELT_FWD } });
}

TEST_F(testAnswerTransferReq, Reset) {
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    test_transition_to<Waiting>( { EventType::EVNT_WRPC_TRNS_RQ }, { { EventType::EVNT_ACK }, {
            EventType::EVNT_ACT_BELT_FWD } });
    data._belt_blocked = true;
    test_transition_to<WaitingForSpace>( { EventType::EVNT_WRPC_TRNS_RQ }, { });
    test_transition_to<Waiting>( { EventType::EVNT_RST_TO_SRT }, { });
}

}
}
}

