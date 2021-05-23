#include <gtest/gtest.h>
#include <vector>

#include "../../logic/datamodel/encoded_workpiece.h"
#include "../../logic/datamodel/workpiece.h"

namespace test {
namespace logic {
namespace datamodel {

using namespace ::logic::datamodel;

void testEncoding(Workpiece& wp){
    wp.determine_type();
    EncodedWorkpiece encoded_wp = wp.encode();
    ASSERT_EQ(wp.get_type(), encoded_wp.get_type());
    ASSERT_EQ(wp.get_id(), encoded_wp.get_id());
    ASSERT_EQ(wp.height_1, encoded_wp.get_height_1());
}

TEST(EncodedWorkpieceTest, WRPC_H) {
    Workpiece wp;
    wp.height_1 = Workpiece::height_high;
    testEncoding(wp);
}

TEST(EncodedWorkpieceTest, WRPC_HM) {
    Workpiece wp;
    wp.height_1 = Workpiece::height_high;
    wp.is_metallic = true;
    testEncoding(wp);
}

TEST(EncodedWorkpieceTest, WRPC_HB) {
    Workpiece wp;
    wp.height_1 = Workpiece::height_bohrung;
    testEncoding(wp);
}

TEST(EncodedWorkpieceTest, WRPC_L) {
    Workpiece wp;
    wp.height_1 = Workpiece::height_low;
    testEncoding(wp);
}

} /*namespace*/
} /*namespace*/
} /*namespace*/
