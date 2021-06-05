#include <gtest/gtest.h>
#include <memory>

#include "logic/datamodel/cb_section.h"
#include "../workpiece_helper.h"

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
    std::shared_ptr<CBSection> p_sec = std::make_shared<CBSection>();
    //add 1
    p_sec->enter_workpiece(create_wp_l());
    ASSERT_EQ(p_sec->workpiece_count(), 1);
    //add 2
    p_sec->enter_workpiece(create_wp_h());
    p_sec->enter_workpiece(create_wp_hb());
    ASSERT_EQ(p_sec->workpiece_count(), 3);
    //pop 1
    p_sec->exit_first_workpiece();
    ASSERT_EQ(p_sec->workpiece_count(), 2);
    //pop to 0
    p_sec->exit_first_workpiece();
    p_sec->exit_first_workpiece();
    ASSERT_EQ(p_sec->workpiece_count(), 0);
}

TEST(CBSectionTest, FirstAndLastWorkpieceShouldReadCorrectSectionContent) {
    std::shared_ptr<CBSection> p_sec = std::make_shared<CBSection>();
    Workpiece wrpc_1 = create_wp_hm();
    Workpiece wrpc_2 = create_wp_h();
    Workpiece wrpc_3 = create_wp_l();

    //add wrpc_1
    p_sec->enter_workpiece(wrpc_1);
    ASSERT_EQ(p_sec->first_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec->last_workpiece().get_id(), wrpc_1.get_id());

    //add wrpc_2
    p_sec->enter_workpiece(wrpc_2);
    ASSERT_EQ(p_sec->first_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec->last_workpiece().get_id(), wrpc_2.get_id());

    //add wrpc_3, pop wrpc_1
    p_sec->enter_workpiece(wrpc_3);
    p_sec->exit_first_workpiece();
    ASSERT_EQ(p_sec->first_workpiece().get_id(), wrpc_2.get_id());
    ASSERT_EQ(p_sec->last_workpiece().get_id(), wrpc_3.get_id());
}

TEST(CBSectionTest, EnteringAndExitingWorkpiecesShouldManifestSectionContent) {
    std::shared_ptr<CBSection> p_sec = std::make_shared<CBSection>();
    Workpiece wrpc_1 = create_wp_hm();
    Workpiece wrpc_2 = create_wp_h();
    Workpiece wrpc_3 = create_wp_l();

    //add wrpc_1
    p_sec->enter_workpiece(wrpc_1);
    ASSERT_EQ(p_sec->first_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec->last_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec->workpiece_count(), 1);

    //add wrpc_2
    p_sec->enter_workpiece(wrpc_2);
    ASSERT_EQ(p_sec->first_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec->last_workpiece().get_id(), wrpc_2.get_id());
    ASSERT_EQ(p_sec->workpiece_count(), 2);

    //add wrpc_3, pop wrpc_1
    p_sec->enter_workpiece(wrpc_3);
    ASSERT_EQ(p_sec->workpiece_count(), 3);
    p_sec->exit_first_workpiece();
    ASSERT_EQ(p_sec->workpiece_count(), 2);
    ASSERT_EQ(p_sec->first_workpiece().get_id(), wrpc_2.get_id());
    ASSERT_EQ(p_sec->last_workpiece().get_id(), wrpc_3.get_id());

    //pop section to 0
    p_sec->exit_first_workpiece();
    p_sec->exit_first_workpiece();
    ASSERT_EQ(p_sec->workpiece_count(), 0);

    //exit on empty section
    p_sec->exit_first_workpiece();
    ASSERT_EQ(p_sec->workpiece_count(), 0);
}

TEST(CBSectionTest, TransferWorkpieceShouldManifestInSectionContent) {
    std::shared_ptr<CBSection> p_sec_3 = std::make_shared<CBSection>();
    std::shared_ptr<CBSection> p_sec_2 = std::make_shared<CBSection>(p_sec_3);
    std::shared_ptr<CBSection> p_sec_1 = std::make_shared<CBSection>(p_sec_2);
    Workpiece wrpc_1 = create_wp_hm();
    Workpiece wrpc_2 = create_wp_h();
    Workpiece wrpc_3 = create_wp_l();

    //add all wrpcs to sec_1
    p_sec_1->enter_workpiece(wrpc_1);
    p_sec_1->enter_workpiece(wrpc_2);
    p_sec_1->enter_workpiece(wrpc_3);

    //transfer wrpc_1 from sec_1 to sec_2
    p_sec_1->transfer_first_workpiece();
    ASSERT_EQ(p_sec_2->last_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec_1->first_workpiece().get_id(), wrpc_2.get_id());
    ASSERT_EQ(p_sec_1->workpiece_count(), 2);
    ASSERT_EQ(p_sec_2->workpiece_count(), 1);
    ASSERT_EQ(p_sec_3->workpiece_count(), 0);

    //transfer wrpc_2 from sec_1 to sec_2
    p_sec_1->transfer_first_workpiece();
    ASSERT_EQ(p_sec_2->first_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec_2->last_workpiece().get_id(), wrpc_2.get_id());
    ASSERT_EQ(p_sec_1->first_workpiece().get_id(), wrpc_3.get_id());
    ASSERT_EQ(p_sec_1->last_workpiece().get_id(), wrpc_3.get_id());
    ASSERT_EQ(p_sec_1->workpiece_count(), 1);
    ASSERT_EQ(p_sec_2->workpiece_count(), 2);
    ASSERT_EQ(p_sec_3->workpiece_count(), 0);

    //transfer wrpc_1 from sec_2 to sec_3
    p_sec_2->transfer_first_workpiece();
    ASSERT_EQ(p_sec_3->first_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec_3->last_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec_2->first_workpiece().get_id(), wrpc_2.get_id());
    ASSERT_EQ(p_sec_2->last_workpiece().get_id(), wrpc_2.get_id());
    ASSERT_EQ(p_sec_1->first_workpiece().get_id(), wrpc_3.get_id());
    ASSERT_EQ(p_sec_1->last_workpiece().get_id(), wrpc_3.get_id());
    ASSERT_EQ(p_sec_1->workpiece_count(), 1);
    ASSERT_EQ(p_sec_2->workpiece_count(), 1);
    ASSERT_EQ(p_sec_3->workpiece_count(), 1);

    //transfer wrpc_3 from sec_1 to sec_2
    p_sec_1->transfer_first_workpiece();
    ASSERT_EQ(p_sec_3->first_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec_3->last_workpiece().get_id(), wrpc_1.get_id());
    ASSERT_EQ(p_sec_2->first_workpiece().get_id(), wrpc_2.get_id());
    ASSERT_EQ(p_sec_2->last_workpiece().get_id(), wrpc_3.get_id());
    ASSERT_EQ(p_sec_1->workpiece_count(), 0);
    ASSERT_EQ(p_sec_2->workpiece_count(), 2);
    ASSERT_EQ(p_sec_3->workpiece_count(), 1);
}

TEST(CBSectionTest, TransferWorkpieceShouldHandleTransferingFromEmptySection) {
    std::shared_ptr<CBSection> p_sec_2 = std::make_shared<CBSection>();
    std::shared_ptr<CBSection> p_sec_1 = std::make_shared<CBSection>(p_sec_2);
    Workpiece wrpc = create_wp_hm();
    p_sec_2->enter_workpiece(wrpc);
    ASSERT_EQ(p_sec_1->workpiece_count(), 0);
    ASSERT_EQ(p_sec_2->workpiece_count(), 1);
    //transfer from empty section
    p_sec_1->transfer_first_workpiece();
    ASSERT_EQ(p_sec_1->workpiece_count(), 0);
    ASSERT_EQ(p_sec_2->workpiece_count(), 1);
}

TEST(CBSectionTest, TransferWorkpieceShouldHandleTransferingAtEndSection) {
    std::shared_ptr<CBSection> p_sec_3 = std::make_shared<CBSection>();
    std::shared_ptr<CBSection> p_sec_2 = std::make_shared<CBSection>(p_sec_3);
    std::shared_ptr<CBSection> p_sec_1 = std::make_shared<CBSection>(p_sec_2);
    Workpiece wrpc_1 = create_wp_hm();
    Workpiece wrpc_2 = create_wp_h();
    Workpiece wrpc_3 = create_wp_l();

    p_sec_3->enter_workpiece(wrpc_1);
    p_sec_2->enter_workpiece(wrpc_2);
    p_sec_1->enter_workpiece(wrpc_3);

    //transfer at end section
    p_sec_3->transfer_first_workpiece();
    ASSERT_EQ(p_sec_1->workpiece_count(), 1);
    ASSERT_EQ(p_sec_2->workpiece_count(), 1);
    ASSERT_EQ(p_sec_3->workpiece_count(), 0);

    //transfer to 0
    p_sec_2->transfer_first_workpiece();
    p_sec_3->transfer_first_workpiece();
    p_sec_1->transfer_first_workpiece();
    p_sec_2->transfer_first_workpiece();
    p_sec_3->transfer_first_workpiece();
    ASSERT_EQ(p_sec_1->workpiece_count(), 0);
    ASSERT_EQ(p_sec_2->workpiece_count(), 0);
    ASSERT_EQ(p_sec_3->workpiece_count(), 0);
}


} /*namespace*/
} /*namespace*/
} /*namespace*/
