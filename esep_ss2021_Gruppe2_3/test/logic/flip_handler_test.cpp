#include "TestClient.h"
#include "../../dispatcher/Event.h"
#include "../../logic/helper/FlipHandler.h"
#include "../../dispatcher/dispatcher.h"
#include "../TestUtils.h"
#include "../../logic/datamodel/unit_data.h"



#include <chrono>
#include <string>

namespace test {
namespace timerTest {

using namespace dispatcher;
using namespace logic;

class FlipHandlerTest: public ::testing::Test {
protected:
    std::shared_ptr<datamodel::UnitData> _data;
    std::unique_ptr<Dispatcher> _dispatcher;
    std::unique_ptr<FlipHandler> _flip_handler;
    std::unique_ptr<TestClient> _testClient;
    FlipHandlerTest() {
        const std::string DISPATCHER_NAME = getUniqueDispatcherName();
        _data = std::shared_ptr<datamodel::UnitData>(new datamodel::UnitData());
        _dispatcher = std::unique_ptr<Dispatcher>(new Dispatcher(DISPATCHER_NAME));
        _flip_handler = std::unique_ptr<FlipHandler>(
                new FlipHandler(DISPATCHER_NAME,_data));
        _testClient = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME, fmt::format("{}_{}", clienetPrefix, __TC_NAME__)));
    }

    void testResetToType(datamodel::Workpiece& wrpc) {
        datamodel::EncodedWorkpiece enc_wrpc = wrpc.encode();
        Event flipped_event = { dispatcher::EventType::EVNT_WRPC_FLP, enc_wrpc.code, false };
        _testClient->send(flipped_event, msg_prio);
        usleep(1000); // wait a bit for a change
        ASSERT_EQ(wrpc.get_type(), _data->get_next_in_order());
    }
};

TEST_F(FlipHandlerTest, ResetsToHoleMetal) {
    datamodel::Workpiece wp_hm;
    wp_hm.height_1 = 91;
    wp_hm.is_metallic = true;
    wp_hm.determine_type();
    this->testResetToType(wp_hm);
}

TEST_F(FlipHandlerTest, ResetsToHole) {
    datamodel::Workpiece wp_hp;
    wp_hp.height_1 = 91;
    wp_hp.is_metallic = false;
    wp_hp.determine_type();
    this->testResetToType(wp_hp);
}

TEST_F(FlipHandlerTest, ResetsToFlat) {
    datamodel::Workpiece wp_f;
    wp_f.height_1 = 210;
    wp_f.is_metallic = false;
    wp_f.determine_type();
    this->testResetToType(wp_f);
}


} /*namespace*/
} /*namespace*/




