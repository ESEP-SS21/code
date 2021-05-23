#include <gtest/gtest.h>
#include <array>

#include "../../logic/datamodel/workpiece.h"

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

TEST(WorkpieceTest, DeterminedTypeShouldBeCorrct) {
    Workpiece wp_l, wp_h, wp_hm, wp_hb;
    wp_l.height_1 = Workpiece::height_low;
    wp_h.height_1 = Workpiece::height_high;
    wp_hb.height_1 = Workpiece::height_bohrung;
    wp_hm.height_1 = Workpiece::height_bohrung;
    wp_hm.is_metallic = true;

    const unsigned int size = 4;
    std::array<Workpiece, size> workpieces { wp_l, wp_h, wp_hm, wp_hb };
    std::array<WorkpieceType, size> workpieces_types { WorkpieceType::WRPC_L, WorkpieceType::WRPC_H,
            WorkpieceType::WRPC_HM, WorkpieceType::WRPC_HB, };

    testWorkpieceTypes<size>(workpieces, workpieces_types);
}

TEST(WorkpieceTest, FlippedShouldBeDeterminedCorrectly) {
    Workpiece wp_hm, wp_hb;
    wp_hb.height_1 = wp_hm.height_1 = Workpiece::height_bohrung;
    wp_hm.is_metallic = true;

    wp_hb.determine_type();
    wp_hm.determine_type();
    ASSERT_FALSE(wp_hb.is_flipped);
    ASSERT_FALSE(wp_hm.is_flipped);

    wp_hb.height_2 = wp_hm.height_2 = Workpiece::height_high;

    wp_hb.determine_type();
    wp_hm.determine_type();
    ASSERT_TRUE(wp_hb.is_flipped);
    ASSERT_TRUE(wp_hm.is_flipped);
}

} /*namespace*/
} /*namespace*/
} /*namespace*/
