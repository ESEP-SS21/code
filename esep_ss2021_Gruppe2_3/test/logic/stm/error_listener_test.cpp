#include <gtest/gtest.h>
#include <logic/stm/StmErrorListener/error_listener_states.h>
#include <logic/stm/StmErrorListener/error_listener_context.h>
#include "util/stm_test_client.h"

#include "util/stm_test_base.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::StmErrorListener;

class testErrorManager : public stm_test_base<ErrorListenerContext, ::logic::datamodel::UnitType::PRIMARY> {
public:
    void switch_to_resolve(){
        test_start_state<WaitingForError>({});
        ASSERT_EQ(data._pending_error, ::logic::datamodel::Error::NO_ERROR);
        test_transition_to<WaitingForResolve>({EventType::EVNT_ERR, (int)::logic::datamodel::Error::RAMP_FULL}, {});
        ASSERT_EQ(data._pending_error, ::logic::datamodel::Error::RAMP_FULL);
    }
};

TEST_F(testErrorManager, switchToWaitingForResolve) {
    switch_to_resolve();
}

TEST_F(testErrorManager, errorSolved) {
    switch_to_resolve();
    test_transition_to<WaitingForError>({EventType::EVNT_SEN_LB_RA_CLR}, {{EventType::EVNT_ERR_GONE}});
    ASSERT_EQ(data._pending_error, ::logic::datamodel::Error::NO_ERROR);
}

TEST_F(testErrorManager, estop) {
    switch_to_resolve();
    test_transition_to<WaitingForError>({EventType::EVNT_SEN_ESTOP_ON}, {});
    ASSERT_EQ(data._pending_error, ::logic::datamodel::Error::NO_ERROR);
}

TEST_F(testErrorManager, connLost) {
    switch_to_resolve();
    test_transition_to<WaitingForError>({EventType::EVNT_CONN_LOST}, {});
    ASSERT_EQ(data._pending_error, ::logic::datamodel::Error::NO_ERROR);
}

}
}
}



