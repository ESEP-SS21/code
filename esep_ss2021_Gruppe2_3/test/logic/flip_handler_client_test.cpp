#include "TestClient.h"
#include "../../dispatcher/Event.h"
#include "../../logic/util/flip_handler_client.h"
#include "../../dispatcher/dispatcher.h"
#include "../TestUtils.h"
#include "../../logic/datamodel/unit_data.h"
#include "../../logic/datamodel/workpiece.h"
#include "workpiece_helper.h"

#include <chrono>
#include <string>

namespace test {
namespace logic {

using namespace ::dispatcher;
using namespace ::logic::util;
using namespace ::logic::datamodel;

class FlipHandlerTest: public ::testing::Test {
protected:
    std::shared_ptr<UnitData> _data;
    std::unique_ptr<Dispatcher> _dispatcher;
    std::unique_ptr<FlipHandlerClient> _flip_handler;
    std::unique_ptr<TestClient> _testClient;
    FlipHandlerTest() {
        const std::string DISPATCHER_NAME = getUniqueDispatcherName();
        _data = std::shared_ptr<UnitData>(new UnitData(OperationMode::PRIMARY));
        _dispatcher = std::unique_ptr<Dispatcher>(new Dispatcher(DISPATCHER_NAME));
        _flip_handler = std::unique_ptr<FlipHandlerClient>(
                new FlipHandlerClient(DISPATCHER_NAME,_data));
        _testClient = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME, fmt::format("{}_{}", clienetPrefix, __TC_NAME__)));
    }

    void testResetToType(Workpiece& wrpc) {
        EncodedWorkpiece enc_wrpc = wrpc.encode();
        Event flipped_event = { EventType::EVNT_WRPC_FLP, (int)enc_wrpc.code, false };
        _testClient->send(flipped_event, msg_prio);
        usleep(1000); // wait a bit for a change
        ASSERT_EQ(wrpc.get_type(), _data->get_next_in_order());
    }
};

TEST_F(FlipHandlerTest, ResetsToHoleMetal) {
    Workpiece wp_hm = create_wp_hm();
    this->testResetToType(wp_hm);
}

TEST_F(FlipHandlerTest, ResetsToHole) {
    Workpiece wp_hb = create_wp_hb();
    this->testResetToType(wp_hb);
}

TEST_F(FlipHandlerTest, ResetsToFlat) {
    Workpiece wp_l = create_wp_l();
    this->testResetToType(wp_l);
}

} /*namespace*/
} /*namespace*/




