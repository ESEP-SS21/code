#include <gtest/gtest.h>
#include "logic/stm/StmSortWrpc/sort_wrpc_context.h"
#include "util/stm_test_client.h"
#include "util/stm_test_base.h"
#include "logic/stm/StmSortWrpc/states/operating_substates/WaitingForWrpc.h"
#include "logic/stm/StmSortWrpc/states/operating_substates/RampFull.h"
#include "logic/stm/StmSortWrpc/states/operating_substates/WaitingForRampToClear.h"
#include "logic/stm/StmSortWrpc/states/wfstc_substates/NoDiscard.h"
#include "logic/stm/StmSortWrpc/states/wfstc_substates/Discard.h"
#include "logic/stm/StmSortWrpc/states/wfstc_substates/WaitingToPass.h"
#include "logic/stm/StmSortWrpc/states/wfstc_substates/WrpcStuck.h"
#include "logic/stm/StmSortWrpc/states/sub_wfstc.h"
#include "logic/stm/StmSortWrpc/states/sub_operating.h"
#include <iostream>

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::sortWrpcStm;
using namespace ::logic::datamodel;

INIT_STM_TEST(testSortWrpc, SortWrpcContext, ::logic::datamodel::UnitType::PRIMARY)

TEST_F(testSortWrpc, BeginsInRightState) {
    ASSERT_STATE(WaitingForWrpc);
}

TEST_F(testSortWrpc, WrpcFitsInSortingOrder) {
    Workpiece wrpc;
    wrpc.height_1 = Workpiece::height_bohrung;
    wrpc.is_metallic = true;
    wrpc.determine_type();
    data._operating_mode = OperatingMode::RUNNING;
    data.get_height_switch_sec()->enter_workpiece(wrpc);
    test_transition_to<NoDiscard>( { EventType::EVNT_SEN_LB_SW_BLCK },
            { { EventType::EVNT_ACT_SORT_NO_DSC } });
}

} /* namespace stm */
} /* namespace logic */
} /* namespace test */

