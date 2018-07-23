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
        l2_ = VList<int>(1);
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
    EXPECT_EQ(*(l2_.begin()), 1);
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

TEST_F(VListTest, AppendTest)
{
    auto old_it = l3_.begin();
    l3_.append(0, &old_it);
    ++old_it;
    EXPECT_EQ(*old_it, 0);
}

TEST_F(VListTest, PrependTest)
{
    auto it = l4_.end();
    l4_.prepend(0, &it);
    auto it_head = l4_.begin();
    EXPECT_EQ(*it_head, 0);
    --it;
    EXPECT_EQ(*it, 0);
}

TEST_F(VListTest, GetTest)
{
    EXPECT_EQ(l5_.get(0), 0);
    EXPECT_EQ(l5_.get(1), 1);
    EXPECT_EQ(l5_.get(2), 2);
}

//TEST_F(VListTest, AssimentTest)
//{
//
//    for (int i = 0; i < l6_.size(); ++i)
//    {
//
//    }
//    EXPECT_EQ(l5_.begin(), l6_.begin());
//}
//
//TEST_F(VListTest, PopBackTest)
//{
//
//}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    const el::Configurations conf("global.conf");
    el::Loggers::reconfigureAllLoggers(conf);

    return RUN_ALL_TESTS();
}