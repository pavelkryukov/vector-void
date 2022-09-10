/*
 * Copyright (c) 2021-2022 Pavel I. Kryukov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../vector_void.hpp"

#include <gtest/gtest.h>

static_assert(sizeof(VectorVoid) == sizeof(std::size_t));

template<typename T>
void check(T& v, std::size_t length)
{
    EXPECT_EQ(v.empty(), length == 0);
    EXPECT_EQ(v.size(), length);
    EXPECT_GE(v.capacity(), v.size());
    EXPECT_THROW(v.at(length), std::out_of_range);
 
    if (length > 0) {
        EXPECT_EQ(v[5], v[2]);
        EXPECT_EQ(v.at(5), v[2]);
        EXPECT_EQ(v.at(5), v.at(4));
    }

    EXPECT_EQ(v.front(), v[0]);
    EXPECT_EQ(v.back(), v[length - 1]);
}

TEST(VectorVoidTest, Empty)
{
    VectorVoid v;
    check(v, 0);
}

TEST(VectorVoidTest, Length10)
{
    VectorVoid v(10);
    check(v, 10);
}

TEST(VectorVoidTest, Clear)
{
    VectorVoid v(10);
    v.clear();
    check(v, 0);
}

TEST(VectorVoidTest, ConstLength10)
{
    const VectorVoid v(10, Void{});
    check(v, 10);
}

TEST(VectorVoidTest, CopyCtor)
{
    const VectorVoid v(10, Void{});
    VectorVoid a(v);

    check(v, 10);
    check(a, 10);
}

TEST(VectorVoidTest, MoveCtor)
{
    VectorVoid v(10, Void{});
    VectorVoid a(std::move(v));

    check(v, 0);
    check(a, 10);
}

TEST(VectorVoidTest, PushBack)
{
    VectorVoid v(10);
    const Void i = v.front();
    v.push_back(i);
    check(v, 11);
}

TEST(VectorVoidTest, PushBackMove)
{
    VectorVoid v(10);
    v.push_back(Void{});
    check(v, 11);
}

TEST(VectorVoidTest, EmplaceBack)
{
    VectorVoid v(10);
    v.emplace_back(Void{});
    v.emplace_back();
    check(v, 12);
}

TEST(VectorVoidTest, PopBack)
{
    VectorVoid v(10);
    v.pop_back();
    check(v, 9);
}

TEST(VectorVoidTest, ResizeDown)
{
    VectorVoid v(10);
    v.resize(6);
    check(v, 6);
}

TEST(VectorVoidTest, ResizeUp)
{
    VectorVoid v(10);
    v.resize(12);
    check(v, 12);
}

TEST(VectorVoidTest, ResizeRefDown)
{
    VectorVoid v(10);
    v.resize(6, Void{});
    check(v, 6);
}

TEST(VectorVoidTest, ResizeRefUp)
{
    VectorVoid v(10);
    v.resize(12, Void{});
    check(v, 12);
}

TEST(VectorVoidTest, Swap)
{
    VectorVoid a(20);
    VectorVoid b(30);

    a.swap(b);

    check(a, 30);
    check(b, 20);
}
