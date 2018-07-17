#include <google/gtest/gtest.h>
#include <easyloggingpp/easylogging++.h>

#include "vlist.h"

using namespace vcommon;

//INITIALIZE_EASYLOGGINGPP

//TEST(VListTest, ConstructorTest)
//{
//    VList<int> v_list;
//    VList<int> v_list_1(10);
//    EXPECT_EQ(v_list_1.head_->next_->data_, 10);
//    EXPECT_EQ(v_list.head_->next_, nullptr);
//    EXPECT_EQ(v_list_1.tail_->next_->data_, 10);
//    EXPECT_EQ(v_list_1.tail_->next_, v_list_1.head_->next_);
//}
//
//TEST(VListTest, IteratorTest)
//{
//    VList<int> v_list(10);
//    EXPECT_EQ(*(v_list.begin()), 10);
//    EXPECT_EQ(*(v_list.end()), 10);
//}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    const el::Configurations conf("global.conf");
    el::Loggers::reconfigureAllLoggers(conf);

    return RUN_ALL_TESTS();
}