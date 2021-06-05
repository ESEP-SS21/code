#include <gtest/gtest.h>
#include <array>

#include "logic/datamodel/workpiece.h"
#include "../workpiece_helper.h"

namespace test {
namespace logic {
namespace datamodel {

using namespace ::logic::datamodel;


template<int size>
void testWorkpieceTypes(std::array<Workpiece, size>& workpieces,
        std::array<WorkpieceType, size>& workpieces_types) {
    for (unsigned int i = 0; i < workpieces.size(); i++) {
        workpieces[i].determine_type();
        ASSERT_EQ(workpieces[i].get_type(), workpieces_types[i]);
    }
}

void testConstructingFromEncodedWorkpiece(Workpiece &workpiece){
    Workpiece reencoded_workpiece(workpiece.encode());
    ASSERT_EQ(workpiece.height_1, reencoded_workpiece.height_1);
    ASSERT_EQ(workpiece.is_metallic, reencoded_workpiece.is_metallic);
    ASSERT_EQ(workpiece.get_type(), reencoded_workpiece.get_type());
    ASSERT_EQ(workpiece.get_id(), reencoded_workpiece.get_id());
}

TEST(WorkpieceTest, DeterminedTypeShouldBeCorrct) {
    Workpiece wp_hm = create_wp_hm();
    Workpiece wp_hb = create_wp_hb();
    Workpiece wp_l = create_wp_l();
    Workpiece wp_h = create_wp_h();
    Workpiece wp_unknown = create_wp_unknown();

    const unsigned int size = 5;
    std::array<Workpiece, size> workpieces { wp_l, wp_h, wp_hm, wp_hb, wp_unknown };
    std::array<WorkpieceType, size> workpieces_types { WorkpieceType::WRPC_L, WorkpieceType::WRPC_H,
            WorkpieceType::WRPC_HM, WorkpieceType::WRPC_HB, WorkpieceType::Unknown };

    testWorkpieceTypes<size>(workpieces, workpieces_types);
}

TEST(WorkpieceTest, FlippedShouldBeDeterminedCorrectly) {
    Workpiece wp_hm = create_wp_hm();
    Workpiece wp_hb = create_wp_hb();

    ASSERT_FALSE(wp_hb.is_flipped);
    ASSERT_FALSE(wp_hm.is_flipped);

    wp_hb.height_2 = wp_hm.height_2 = Workpiece::height_high;

    wp_hb.determine_type();
    wp_hm.determine_type();
    ASSERT_TRUE(wp_hb.is_flipped);
    ASSERT_TRUE(wp_hm.is_flipped);
}

TEST(WorkpieceTest, CreationFromEncodedWorkpiece) {
    Workpiece wp_hm = create_wp_hm();
    Workpiece wp_hb = create_wp_hb();

    testConstructingFromEncodedWorkpiece(wp_hb);
    testConstructingFromEncodedWorkpiece(wp_hm);
}

} /*namespace*/
} /*namespace*/
} /*namespace*/
