#include <google/gtest/gtest.h>
#include <easyloggingpp/easylogging++.h>

#include "vlist.h"

using namespace vcommon;

INITIALIZE_EASYLOGGINGPP

TEST(VListTest, ConstructorTest)
{
    VList<int> v_list;
    VList<int> v_list_1(10);
    EXPECT_EQ(v_list_1.head_->data_, 10);
    LOG(INFO) << "test";
    EXPECT_EQ(v_list.head_->next_, nullptr);
}

TEST(VListTest, IteratorTest)
{
    VList<int> v_list(10);
    EXPECT_EQ(*(v_list.begin()), 10);
    EXPECT_EQ(*(v_list.end()), 10);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    el::Loggers::configureFromGlobal("globa.conf");

    return RUN_ALL_TESTS();
}