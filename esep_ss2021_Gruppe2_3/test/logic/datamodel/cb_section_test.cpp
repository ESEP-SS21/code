#include <gtest/gtest.h>
#include <memory>

#include "../../logic/datamodel/cb_section.h"

namespace test {
namespace logic {
namespace datamodel {

using namespace ::logic::datamodel;

TEST(CBSectionTest, CBSectionCreationShouldLinkMultipleSectionsCorrectly) {
    std::shared_ptr<CBSection> p_sec_3 = std::make_shared<CBSection>();
    std::shared_ptr<CBSection> p_sec_2 = std::make_shared<CBSection>(p_sec_3);
    std::shared_ptr<CBSection> p_sec_1 = std::make_shared<CBSection>(p_sec_2);
    ASSERT_EQ(p_sec_3->get_next_section(), nullptr);
    ASSERT_EQ(p_sec_2->get_next_section(), p_sec_3);
    ASSERT_EQ(p_sec_1->get_next_section(), p_sec_2);
    ASSERT_EQ(p_sec_3->workpiece_count(), 0);
    ASSERT_EQ(p_sec_2->workpiece_count(), 0);
    ASSERT_EQ(p_sec_1->workpiece_count(), 0);
}

TEST(CBSectionTest, WorkpieceCountShouldCountWorkpiecesCorrectly) {
    //TODO
}

TEST(CBSectionTest, EnteringAndExitingWorkpiecesShouldManifestInWorkpieceCount) {
    //TODO
}

TEST(CBSectionTest, FirstAndLastWorpieceShouldReturnCorrespondingWorkpieces) {
    //TODO
}

TEST(CBSectoinTest, TransferWorkpieceShouldManifestInQueueStructure) {
    //TODO
}

TEST(CBSectionTest, CBSectionCreation) {
    //TODO
}


} /*namespace*/
} /*namespace*/
} /*namespace*/
