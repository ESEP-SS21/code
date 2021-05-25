#include <gtest/gtest.h>
#include <memory>

#include "../../logic/datamodel/cb_section.h"
#include "workpiece_helper.h"

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
    ASSERT_EQ(p_sec_3->get_queue()->size(), 0);
    ASSERT_EQ(p_sec_2->get_queue()->size(), 0);
    ASSERT_EQ(p_sec_1->get_queue()->size(), 0);
}

TEST(CBSectionTest, WorkpieceCountShouldCountWorkpiecesCorrectly) {
    std::shared_ptr<CBSection> p_sec = std::make_shared<CBSection>();
    //add 1
    p_sec->get_queue()->push(create_wp_l());
    ASSERT_EQ(p_sec->workpiece_count(), 1);
    //add 2
    p_sec->get_queue()->push(create_wp_h());
    p_sec->get_queue()->push(create_wp_hb());
    ASSERT_EQ(p_sec->workpiece_count(), 3);
    //pop 1
    p_sec->get_queue()->pop();
    ASSERT_EQ(p_sec->workpiece_count(), 2);
    //pop to 0
    p_sec->get_queue()->pop();
    p_sec->get_queue()->pop();
    ASSERT_EQ(p_sec->workpiece_count(), 0);
}

TEST(CBSectionTest, FirstAndLastWorpieceShouldReturnCorrespondingWorkpieces) {
    std::shared_ptr<CBSection> p_sec = std::make_shared<CBSection>();
    Workpiece wrpc_1 = create_wp_hm();
    Workpiece wrpc_2 = create_wp_h();
    Workpiece wrpc_3 = create_wp_l();

    //add wrpc_1
    p_sec->get_queue()->push(wrpc_1);
    //ASSERT_EQ(p_sec->first_workpiece(), wrpc_1);
    //ASSERT_EQ(p_sec->last_workpiece(), wrpc_1);
}

TEST(CBSectionTest, EnteringAndExitingWorkpiecesShouldManifestQueueContent) {
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
