#include <algorithm>

#include <google/gtest/gtest.h>
#include <easyloggingpp/easylogging++.h>

#include "vlist.h"

using namespace std;
using namespace vcommon;

INITIALIZE_EASYLOGGINGPP

TEST(VListTest, ConstructorTest)
{
    VList<int> v_list;
    VList<int> v_list_1(10);
    EXPECT_EQ(v_list_1.head_->next_->data_, 10);
}

TEST(VListTest, IteratorTest)
{
    VList<int> v_list(10);
    EXPECT_EQ(*(v_list.begin()), 10);
}

TEST(VListTest, PushBackTest)
{
    VList<int> v_list(1);
    v_list.push_back(2);
    v_list.push_back(3);
    v_list.push_front(0);

    int i = 0;
    for (auto it = v_list.begin(); it != v_list.end(); ++it)
    {
        EXPECT_EQ(*it, i++);
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    const el::Configurations conf("global.conf");
    el::Loggers::reconfigureAllLoggers(conf);

    return RUN_ALL_TESTS();
}