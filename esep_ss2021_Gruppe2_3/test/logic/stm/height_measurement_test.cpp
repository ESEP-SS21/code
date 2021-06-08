#include <gtest/gtest.h>
#include "util/stm_test_client.h"
#include "util/stm_test_base.h"
#include "logic/stm/StmHeightMeasurement/height_measurement_states.h"
#include "logic/stm/StmHeightMeasurement/height_measurement_context.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::StmHeightMeasurement;
using namespace ::logic::datamodel;

INIT_STM_TEST(testHeightMeasurementPrimary, HeightMeasurementContext, UnitType::PRIMARY)
INIT_STM_TEST(testHeightMeasurementSecondary, HeightMeasurementContext, UnitType::SECONDARY)

TEST_F(testHeightMeasurementPrimary, BeginsInRightState) {
    ASSERT_STATE(WaitingForWorkpiece);
}

TEST_F(testHeightMeasurementPrimary, RegularMeasurementInPrimary) {
    ASSERT_EQ(data._unit_type, UnitType::PRIMARY);
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc;
    data.get_start_height_sec()->enter_workpiece(wrpc);

    // WaitingForWorkpiece -> WaitingForHeight
    test_transition_to<WaitingForHeight>( { EventType::EVNT_SEN_LB_HE_BLCK }, { {
            EventType::EVNT_SEN_HEIGHT_REQ } });

    ASSERT_FALSE(data._belt_blocked);
    ASSERT_EQ(0, data.get_start_height_sec()->workpiece_count());
    ASSERT_EQ(1, data.get_height_switch_sec()->workpiece_count());
    ASSERT_EQ(wrpc, data.get_height_switch_sec()->last_workpiece());

    test_transition_to<WaitingForWorkpiece>( { EventType::EVNT_SEN_HEIGHT_HE, 215 }, { });
    ASSERT_EQ(data.get_height_switch_sec()->last_workpiece().height_1, 215);
    wrpc.determine_type();
    ASSERT_EQ(data.get_height_switch_sec()->last_workpiece().get_type(), WorkpieceType::WRPC_L);

    //TODO write function to test all heights
}

TEST_F(testHeightMeasurementSecondary, MeasurementOfFlippedWrpcInSecondary) {
    ASSERT_EQ(data._unit_type, UnitType::SECONDARY);
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc;
    wrpc.height_1 = Workpiece::height_bohrung;
    data.get_start_height_sec()->enter_workpiece(wrpc);

    test_transition_to<WaitingForHeight>( { EventType::EVNT_SEN_LB_HE_BLCK }, { {
            EventType::EVNT_SEN_HEIGHT_REQ } });
    ASSERT_FALSE(data._belt_blocked);
    ASSERT_EQ(0, data.get_start_height_sec()->workpiece_count());
    ASSERT_EQ(1, data.get_height_switch_sec()->workpiece_count());
    ASSERT_EQ(wrpc, data.get_height_switch_sec()->last_workpiece());

    auto enc_wrpc = data.get_height_switch_sec()->last_workpiece().encode();

    test_transition_to<WaitingForWorkpiece>(
            { EventType::EVNT_SEN_HEIGHT_HE, Workpiece::height_high }, { { EventType::EVNT_WRPC_FLP,
                    enc_wrpc.code } });

    ASSERT_EQ(data.get_height_switch_sec()->last_workpiece().height_1,
            static_cast<int>(Workpiece::height_bohrung));
    ASSERT_EQ(data.get_height_switch_sec()->last_workpiece().height_2,
            static_cast<int>(Workpiece::height_high));
    ASSERT_TRUE(data.get_height_switch_sec()->last_workpiece().is_flipped);
}

} /* namespace stm */
} /* namespace logic */
} /* namespace test */

