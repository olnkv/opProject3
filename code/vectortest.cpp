#include "vector.h"
#include <gtest/gtest.h>

TEST(VectorTest, Constructor)
{
    MyVector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_EQ(v.empty(), true);
}

TEST(VectorTest, Copy_Consytuctor)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    MyVector<int> v2(v);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2.capacity(), 2);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.capacity(), 2);
    EXPECT_EQ(v.empty(), false);
}

TEST(VectorTest, Move_Constructor)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    MyVector<int> v2;
    v2 = std::move(v);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2.capacity(), 2);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.empty(), true);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
}

TEST(VectorTest, Copy_Operator)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    MyVector<int> v2;
    v2 = v;
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2.capacity(), 2);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.capacity(), 2);
    EXPECT_EQ(v.empty(), false);
}

TEST(VectorTest, initializer_list)
{
    MyVector<std::string> v = {"Edvin", "A", "B"};
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 3);
    EXPECT_EQ(v.empty(), false);
    EXPECT_EQ(v[0], "Edvin");
    EXPECT_EQ(v[1], "A");
    EXPECT_EQ(v[2], "B");
}

TEST(VectorTest, Move_Operator)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    MyVector<int> v2(std::move(v));
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v2.capacity(), 2);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v.empty(), true);
}

TEST(VectorTest, Operator_)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, At)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_THROW(v.at(2), std::out_of_range);
}

TEST(VectorTest, Front)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.front(), 1);
}

TEST(VectorTest, Back)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, Data)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.data()[0], 1);
    EXPECT_EQ(v.data()[1], 2);
}

TEST(VectorTest, Begin)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(*v.begin(), 1);
}

TEST(VectorTest, End)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(*(v.end() - 1), 2);
}

TEST(VectorTest, Capacity)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.capacity(), 2);
}

TEST(VectorTest, Size)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.size(), 2);
    v.push_back(3);
    EXPECT_EQ(v.size(), 3);
}

TEST(VectorTest, Empty)
{
    MyVector<int> v;
    EXPECT_EQ(v.empty(), true);
    v.push_back(1);
    EXPECT_EQ(v.empty(), false);
}

TEST(VectorTest, Reserve)
{
    MyVector<int> v;
    EXPECT_EQ(v.capacity(), 0);
    v.reserve(10);
    EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorTest, Shrink_to_fit)
{
    MyVector<int> v;
    v.reserve(10);
    v.push_back(1);
    v.push_back(2);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 2);
}

TEST(VectorTest, Assign)
{
    MyVector<int> v;
    v.assign(10, 5);
    EXPECT_EQ(v.size(), 10);
    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(v[i], 5);
    }
}

TEST(VectorTest, Clear)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.size(), 2);
    v.clear();
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, Push_Back)
{
    MyVector<int> v;
    v.push_back(1);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity(), 1);
    EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, Emplace)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.emplace(1, 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 2);
}

TEST(VectorTest, Emplace_Back)
{
    MyVector<int> v;
    v.push_back(1);
    v.emplace_back(2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.capacity(), 2);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, Pop_Back)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.size(), 3);
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_THROW(v.at(2), std::out_of_range);
}

TEST(VectorTest, Resize)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.size(), 2);
    v.resize(4);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 0);
    EXPECT_EQ(v[3], 0);
}

TEST(VectorTest, Swap)
{
    MyVector<int> v1;
    v1.reserve(10);
    v1.push_back(1);
    v1.push_back(2);
    MyVector<int> v2;
    v2.push_back(3);
    v2.push_back(4);
    v1.swap(v2);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v1.capacity(), 2);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2.capacity(), 10);
    EXPECT_EQ(v1[0], 3);
    EXPECT_EQ(v1[1], 4);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
}

TEST(VectorTest, Insert)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.insert(1, 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 2);
}

TEST(VectorTest, Erase1)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.erase(1);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Erase2)
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    int *begin = v.data() + 1;
    int *end = v.data() + 3;
    int *result = v.erase(begin, end);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 4);
    EXPECT_EQ(v[2], 5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}