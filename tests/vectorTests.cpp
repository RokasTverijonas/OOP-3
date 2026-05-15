#include <gtest/gtest.h>
#include "vector.h"

//konstruktoriai
TEST(VectorTest, DefaultConstructor)
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_TRUE(v.empty());

}
TEST(VectorTest, InitializerListConstructor)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);

}
TEST(VectorTest, CopyConstructor)
{
    Vector<int> a = {1, 2, 3};
    Vector<int> b(a);
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);

}
TEST(VectorTest, MoveConstructor)
{
    Vector<int> a = {1, 2, 3};
    Vector<int> b(std::move(a));
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);

}
//operatoriai
TEST(VectorTest, CopyAssignment)
{
    Vector<int> a = {1, 2, 3};
    Vector<int> b;
    b = a;
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}
TEST(VectorTest, MoveAssignment)
{
    Vector<int> a = {1, 2, 3};
    Vector<int> b;
    b = std::move(a);
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}
TEST(VectorTest, SubscriptOperator)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v[1], 2);
    v[1] = 10;
    EXPECT_EQ(v[1], 10);
}
TEST(VectorTest, OperatorEquals)
{
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {1, 2, 3};
    Vector<int> c = {10, 20, 30};
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}
TEST(VectorTest, OperatorNotEquals)
{
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {10, 20, 30};
    EXPECT_TRUE(a != b);
}
TEST(VectorTest, AtMethod)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.at(2), 3);
}
TEST(VectorTest, FrontMethod)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.front(), 1);
}
TEST(VectorTest, BackMethod)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.back(), 3);
}
TEST(VectorTest, DataMethod)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.data()[0], 1);
}

TEST(VectorTest, Empty)
{
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    v.push_back(200);
    EXPECT_FALSE(v.empty());
}
TEST(VectorTest, Size)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.size(), 3);
}
TEST(VectorTest, Capacity)
{
    Vector<int> v;
    v.reserve(20);
    EXPECT_EQ(v.capacity(), 20);
}
TEST(VectorTest, Reserve)
{
    Vector<int> v;
    v.reserve(20);
    EXPECT_EQ(v.capacity(), 20);
    EXPECT_EQ(v.size(), 0);
}
TEST(VectorTest, ShrinkToFit)
{
    Vector<int> v;
    v.reserve(20);
    v.push_back(2);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 1);
}

TEST(VectorTest, PushBack)
{
    Vector<int> v;
    v.push_back(2);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 2);
}
TEST(VectorTest, PopBack)
{
    Vector<int> v = {1, 2, 3};
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 2);
}
TEST(VectorTest, Clear)
{
    Vector<int> v = {1, 2, 3};
    v.clear();
    EXPECT_EQ(v.size(), 0);
}
TEST(VectorTest, Resize)
{
    Vector<int> v = {1, 2, 3};
    v.resize(2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 2);
}
TEST(VectorTest, Assign)
{
    Vector<int> v;
    v.assign(2, 3);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 3);
    EXPECT_EQ(v[1], 3);
}
TEST(VectorTest, Insert)
{
    Vector<int> v = {1, 2, 3};
    v.insert(v.begin() + 1, 100);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[1], 100);
    EXPECT_EQ(v[3], 3);
}
TEST(VectorTest, InsertRange)
{
    Vector<int> v = {1, 2, 3};
    Vector<int> extra = {10, 20};
    v.insert(v.begin() + 1, extra.begin(), extra.end());
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[1], 10);
    EXPECT_EQ(v[2], 20);
}
TEST(Vector, EraseRange)
{
    Vector<int> v = {1, 2, 3, 4, 5};
    v.erase(v.begin() + 1, v.begin() + 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[1], 4);
}
TEST(VectorTest, Erase)
{
    Vector<int> v = {1, 2, 3};
    v.erase(v.begin() + 2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[1], 2);
}
TEST(VectorTest, Swap)
{
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {4, 5};
    a.swap(b);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(a.back(), 5);
    EXPECT_EQ(b.back(), 3);
}

//iteratoriai
TEST(VectorTest, BeginEnd)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(*v.begin(), 1);
    EXPECT_EQ(*(v.end() - 1), 3);
}
TEST(VectorTest, CbeginEnd)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1);
    EXPECT_EQ(*(v.cend() - 1), 3);
}



 