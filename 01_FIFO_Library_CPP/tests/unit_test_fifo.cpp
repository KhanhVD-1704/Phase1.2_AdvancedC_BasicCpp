#include "unit_test_fifo.hpp"

#include <cassert>
#include <iostream>

#include "fifo.hpp"

using namespace fifo_library;

#define EXPECT_TRUE(expr)      assert(expr)
#define EXPECT_FALSE(expr)     assert(!(expr))
#define EXPECT_EQ(a, b)        assert((a) == (b))

/*====================================================
=                Constructor Test                    =
====================================================*/

void TestConstructor()
{
    std::cout << "\n========== TestConstructor ==========\n";

    FIFO fifo(5);

    EXPECT_EQ(fifo.Capacity(), 5U);
    EXPECT_EQ(fifo.Size(), 0U);
    EXPECT_TRUE(fifo.IsEmpty());
    EXPECT_FALSE(fifo.IsFull());

    fifo.DebugPrint();

    std::cout << "[PASS] TestConstructor\n";
}

/*====================================================
=                Push Test                           =
====================================================*/

void TestPush()
{
    std::cout << "\n========== TestPush ==========\n";

    FIFO fifo(3);

    EXPECT_TRUE(fifo.Push(10));
    fifo.DebugPrint();

    EXPECT_TRUE(fifo.Push(20));
    fifo.DebugPrint();

    EXPECT_TRUE(fifo.Push(30));
    fifo.DebugPrint();

    EXPECT_TRUE(fifo.IsFull());

    EXPECT_FALSE(fifo.Push(40));

    fifo.DebugPrint();

    std::cout << "[PASS] TestPush\n";
}

/*====================================================
=                Pop Test                            =
====================================================*/

void TestPop()
{
    std::cout << "\n========== TestPop ==========\n";

    FIFO fifo(3);

    fifo.Push(10);
    fifo.Push(20);
    fifo.Push(30);

    fifo.DebugPrint();

    uint8_t value;

    EXPECT_TRUE(fifo.Pop(value));
    EXPECT_EQ(value, 10);
    fifo.DebugPrint();

    EXPECT_TRUE(fifo.Pop(value));
    EXPECT_EQ(value, 20);
    fifo.DebugPrint();

    EXPECT_TRUE(fifo.Pop(value));
    EXPECT_EQ(value, 30);
    fifo.DebugPrint();

    EXPECT_TRUE(fifo.IsEmpty());

    EXPECT_FALSE(fifo.Pop(value));

    std::cout << "[PASS] TestPop\n";
}

/*====================================================
=                Clear Test                          =
====================================================*/

void TestClear()
{
    std::cout << "\n========== TestClear ==========\n";

    FIFO fifo(5);

    fifo.Push(10);
    fifo.Push(20);
    fifo.Push(30);

    fifo.DebugPrint();

    fifo.Clear();

    fifo.DebugPrint();

    EXPECT_EQ(fifo.Size(), 0U);
    EXPECT_TRUE(fifo.IsEmpty());

    std::cout << "[PASS] TestClear\n";
}

/*====================================================
=             Circular Buffer Test                   =
====================================================*/

void TestWrapAround()
{
    std::cout << "\n========== TestWrapAround ==========\n";

    FIFO fifo(3);

    uint8_t value;

    fifo.Push(1);
    fifo.Push(2);
    fifo.Push(3);

    fifo.DebugPrint();

    fifo.Pop(value);
    fifo.Pop(value);

    fifo.DebugPrint();

    fifo.Push(4);
    fifo.Push(5);

    fifo.DebugPrint();

    EXPECT_TRUE(fifo.Pop(value));
    EXPECT_EQ(value, 3);

    EXPECT_TRUE(fifo.Pop(value));
    EXPECT_EQ(value, 4);

    EXPECT_TRUE(fifo.Pop(value));
    EXPECT_EQ(value, 5);

    fifo.DebugPrint();

    EXPECT_TRUE(fifo.IsEmpty());

    std::cout << "[PASS] TestWrapAround\n";
}

/*====================================================
=                Debug Print Test                    =
====================================================*/

void TestDebugPrint()
{
    std::cout << "\n========== TestDebugPrint ==========\n";

    FIFO fifo(5);

    fifo.Push(11);
    fifo.Push(22);
    fifo.Push(33);

    fifo.DebugPrint();

    std::cout << "[PASS] TestDebugPrint\n";
}

/*====================================================
=                Run All Tests                       =
====================================================*/

void RunAllTests()
{
    std::cout << "========== FIFO UNIT TEST ==========\n";

    TestConstructor();

    TestPush();

    TestPop();

    TestClear();

    TestWrapAround();

    TestDebugPrint();

    std::cout << "\n====================================\n";
    std::cout << " ALL UNIT TESTS PASSED\n";
    std::cout << "====================================\n";
}