#include <gtest/gtest.h>
#include <memory>

#include "../../logic/datamodel/cb_section.h"

namespace test {
namespace logic {
namespace datamodel {

using namespace ::logic::datamodel;

TEST(CBSectionTest, CBSectionCreationShouldLinkMultipleSectionsCorrectly) {
    std::shared_ptr<CBSection> p_sec_2 = std::make_shared<CBSection>();
    std::shared_ptr<CBSection> p_sec_1 = std::make_shared<CBSection>(p_sec_2);
    ASSERT_EQ(p_sec_2->get_queue(), nullptr);

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
