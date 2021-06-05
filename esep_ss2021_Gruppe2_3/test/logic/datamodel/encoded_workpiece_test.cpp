#include <gtest/gtest.h>

#include "logic/datamodel/encoded_workpiece.h"
#include "logic/datamodel/workpiece.h"
#include "../workpiece_helper.h"

namespace test {
namespace logic {
namespace datamodel {

using namespace ::logic::datamodel;

void testEncoding(Workpiece& wp){
    EncodedWorkpiece encoded_wp = wp.encode();
    ASSERT_EQ(wp.get_type(), encoded_wp.get_type());
    ASSERT_EQ(wp.get_id(), encoded_wp.get_id());
    ASSERT_EQ(wp.height_1, encoded_wp.get_height_1());
}

TEST(EncodedWorkpieceTest, WRPC_H) {
    Workpiece wp_h = create_wp_h();
    testEncoding(wp_h);
}

TEST(EncodedWorkpieceTest, WRPC_HM) {
    Workpiece wp_hm = create_wp_h();
    testEncoding(wp_hm);
}

TEST(EncodedWorkpieceTest, WRPC_HB) {
    Workpiece wp_hb = create_wp_hb();
    testEncoding(wp_hb);
}

TEST(EncodedWorkpieceTest, WRPC_L) {
    Workpiece wp_l = create_wp_l();
    testEncoding(wp_l);
}

} /*namespace*/
} /*namespace*/
} /*namespace*/
