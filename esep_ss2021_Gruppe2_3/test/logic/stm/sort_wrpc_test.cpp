#include <gtest/gtest.h>
#include "logic/stm/StmSortWrpc/sort_wrpc_context.h"
#include "util/stm_test_client.h"
#include "util/stm_test_base.h"
#include "logic/stm/StmSortWrpc/states/operating_substates/WaitingForWrpc.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::sortWrpcStm;

INIT_STM_TEST(testSortWrpc, SortWrpcContext,
        ::logic::datamodel::UnitType::PRIMARY)

TEST_F(testSortWrpc, BeginsInRightState) {
    ASSERT_STATE(WaitingForWrpc);
}

} /* namespace stm */
} /* namespace logic */
} /* namespace test */

