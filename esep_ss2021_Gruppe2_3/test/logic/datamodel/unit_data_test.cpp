#include <gtest/gtest.h>
#include <memory>

#include "logic/datamodel/unit_data.h"
#include "../workpiece_helper.h"

namespace test {
namespace logic {
namespace datamodel {

using namespace ::logic::datamodel;

TEST(UnitDataTest, ConstructorShouldCreateThreeCBSectionsInOrder) {
    std::shared_ptr<UnitData> unit_data = std::make_shared<UnitData>(UnitType::PRIMARY);
    ASSERT_EQ(unit_data->get_pending_transfer(), nullptr);
    ASSERT_EQ(unit_data->_belt_blocked, false);
    ASSERT_EQ(unit_data->_ramp_full, false);
    ASSERT_EQ(unit_data->_estop_count, 0);
    ASSERT_EQ(unit_data->_warning_count, 0);

    ASSERT_EQ(unit_data->get_start_height_sec()->get_next_section(), unit_data->get_height_switch_sec());
    ASSERT_EQ(unit_data->get_height_switch_sec()->get_next_section(), unit_data->get_switch_end_sec());
    ASSERT_EQ(unit_data->get_switch_end_sec()->get_next_section(), nullptr);
}

TEST(UnitDataTest, OrderStepShouldStepCorrectly) {
    std::shared_ptr<UnitData> unit_data = std::make_shared<UnitData>(UnitType::PRIMARY);
    ASSERT_EQ(unit_data->get_next_in_order(), WorkpieceType::WRPC_HM);
    unit_data->wrpc_order_step();
    ASSERT_EQ(unit_data->get_next_in_order(), WorkpieceType::WRPC_HB);
    unit_data->wrpc_order_step();
    ASSERT_EQ(unit_data->get_next_in_order(), WorkpieceType::WRPC_L);
    unit_data->wrpc_order_step();
    ASSERT_EQ(unit_data->get_next_in_order(), WorkpieceType::WRPC_HM);
}

TEST(UnitDataTest, OrderResetShouldResetCorrectly) {
    std::shared_ptr<UnitData> unit_data = std::make_shared<UnitData>(UnitType::PRIMARY);
    ASSERT_EQ(unit_data->get_next_in_order(), WorkpieceType::WRPC_HM);
    unit_data->wrpc_order_reset(WorkpieceType::WRPC_L);
    ASSERT_EQ(unit_data->get_next_in_order(), WorkpieceType::WRPC_L);
    unit_data->wrpc_order_reset(WorkpieceType::WRPC_HB);
    ASSERT_EQ(unit_data->get_next_in_order(), WorkpieceType::WRPC_HB);
}

TEST(UnitDataTest, FitsOrderShouldWorkCorrectly) {
    std::shared_ptr<UnitData> unit_data = std::make_shared<UnitData>(UnitType::PRIMARY);
    //in order
    Workpiece wrpc_hm = create_wp_hm();
    Workpiece wrpc_hb = create_wp_hb();
    Workpiece wrpc_l = create_wp_l();
    //not in order
    Workpiece wrpc_h = create_wp_h();
    Workpiece wrpc_unknown = create_wp_unknown();

    ASSERT_TRUE(unit_data->wrpc_fits_order(wrpc_hm));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_hb));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_l));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_h));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_unknown));

    unit_data->wrpc_order_step();

    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_hm));
    ASSERT_TRUE(unit_data->wrpc_fits_order(wrpc_hb));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_l));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_h));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_unknown));

    unit_data->wrpc_order_step();

    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_hm));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_hb));
    ASSERT_TRUE(unit_data->wrpc_fits_order(wrpc_l));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_h));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_unknown));

    unit_data->wrpc_order_step();

    ASSERT_TRUE(unit_data->wrpc_fits_order(wrpc_hm));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_hb));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_l));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_h));
    ASSERT_FALSE(unit_data->wrpc_fits_order(wrpc_unknown));
}


} /*namespace*/
} /*namespace*/
} /*namespace*/
