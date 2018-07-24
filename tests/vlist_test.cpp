#include <algorithm>

#include <google/gtest/gtest.h>
#include <easyloggingpp/easylogging++.h>

#include "vlist.h"

using namespace std;
using namespace vcommon;

INITIALIZE_EASYLOGGINGPP

class VListTest : public testing::Test
{
protected:
    void SetUp() override
    {
        l5_.push_back(0);
        l5_.push_back(1);
        l5_.push_back(2);
        l6_ = l5_;
    }

    VList<int> l1_;
    VList<int> l2_;
    VList<int> l3_;
    VList<int> l4_;
    VList<int> l5_;
    VList<int> l6_;
    VList<int> l7_;
};

TEST_F(VListTest, DefaultConstructorTest)
{
    EXPECT_EQ(l1_.size(), 0);
    EXPECT_TRUE(l1_.empty());
}

TEST_F(VListTest, ConstructorTest)
{
    auto l2 = VList<int>(1);
    EXPECT_EQ(*(l2.begin()), 1);
}

TEST_F(VListTest, PushBackTest)
{
    l1_.push_back(1);
    EXPECT_EQ(*(l1_.begin()), 1);
}

TEST_F(VListTest, PushFrontTest)
{
    l2_.push_front(0);
    EXPECT_EQ(*(l2_.begin()), 0);
}

TEST_F(VListTest, GetTest)
{
    EXPECT_EQ(l5_.get(0), 0);
    EXPECT_EQ(l5_.get(1), 1);
    EXPECT_EQ(l5_.get(2), 2);
    auto & elem_0 = l5_.get(0);
    elem_0 = 3;
    auto & elem_1 = l5_.get(1);
    elem_1 = 4;
    auto & elem_2 = l5_.get(2);
    elem_2 = 5;
    EXPECT_EQ(l5_.get(0), 3);
    EXPECT_EQ(l5_.get(1), 4);
    EXPECT_EQ(l5_.get(2), 5);
}

TEST_F(VListTest, PopFrontTest)
{
    l6_.pop_front();
    EXPECT_EQ(l6_.get(0), 1);
    EXPECT_EQ(l6_.size(), 2);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    const el::Configurations conf("global.conf");
    el::Loggers::reconfigureAllLoggers(conf);

    return RUN_ALL_TESTS();
}