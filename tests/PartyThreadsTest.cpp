/*
 *  PartyThreadsTest.cpp
 *  PartyThreads
 *
 *  Copyright (c) 2019 Salvatore Rivieccio. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <gtest/gtest.h>
#include "../include/PartyThreads.h"

TEST(PartyThreadsTest, Init)
{
    PartyThreads::Pool pt;
}

TEST(PartyThreadsTest, Resize)
{
    PartyThreads::Pool pt{2};
}

TEST(PartyThreadsTest, Push)
{
    PartyThreads::Pool pt;
    auto lambda = [] (const int i)
    {
        std::cout << "Hello, " << i << std::endl;
    };
    pt.push(lambda, 1);
    pt.stop(true);
}

TEST( PartyThreadsTest, PushAndWaitFuture )
{
    PartyThreads::Pool pt;
    auto lambda = [] (const int i)
    {
        std::cout << "Hello, " << i << std::endl;
        return i;
    };
    auto future = pt.push(lambda, 1);
    ASSERT_EQ(future.get(), 1);
    pt.stop(true);
}

TEST(PartyThreadsTest, Stop)
{
    PartyThreads::Pool pt;
    pt.stop(true);
}

TEST(PartyThreadsTest, StopNoWait)
{
    PartyThreads::Pool pt;
    pt.stop(false);
}

TEST(PartyThreadsTest, ClearQueue)
{
    PartyThreads::Pool pt;
    pt.clearQueue();
}

TEST(PartyThreadsTest, Size)
{
    const PartyThreads::Pool pt;
    ASSERT_GT(pt.size(), 0);
}

TEST(PartyThreadsTest, NIdle)
{
    PartyThreads::Pool pt;
    ASSERT_GT(pt.nIdle(), 0);
}

TEST(PartyThreadsTest, Destructor)
{
    const auto *pt = new PartyThreads::Pool();
    delete pt;
}

TEST(PartyThreadsTest, MultipleThreadsStop)
{
    PartyThreads::Pool pt{3};
    auto lambda = [] (const int i)
    {
        std::cout << "Hello, " << i << std::endl;
        return i;
    };
    
    auto future1 = pt.push(lambda, 1);
    auto future2 = pt.push(lambda, 2);
    ASSERT_EQ(future1.get(), 1);
    ASSERT_EQ(future2.get(), 2);
    pt.stop(true);
}

TEST( PartyThreadsTest, MultipleThreadsStopNoWait )
{
    PartyThreads::Pool pt{3};
    auto lambda = [] (const int i)
    {
        std::cout << "Hello, " << i << std::endl;
        return i;
    };
    
    auto future1 = pt.push(lambda, 1);
    auto future2 = pt.push(lambda, 2);
    ASSERT_EQ(future1.get(), 1);
    ASSERT_EQ(future2.get(), 2);
    pt.stop(false);
}

TEST(PartyThreadsTest, LongTimeExcutionMultipleThreads)
{
    PartyThreads::Pool pt{10};
    bool stop = false;
    auto lambda = [] (const int i, const bool &s)
    {
        while (!s)
        {
            std::cout << "Hello, " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        return 0;
    };

    std::vector<std::future<int>> futures;
    futures.reserve(10);
    for( int i = 0; i < 10; ++i)
    {
        futures.emplace_back(pt.push(lambda, i, std::ref(stop)));
    }
    stop = true;
    for( auto &f : futures)
    {
        ASSERT_EQ(f.get(), 0);
    }
    pt.stop(true);
}
