#include "unit_test_fifo.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "fifo.hpp"

using fifo_library::FIFO;

#define EXPECT_TRUE(expr)                                                    \
    do                                                                       \
    {                                                                        \
        if (!(expr))                                                         \
        {                                                                    \
            std::cerr << "[FAIL] " << __func__ << ": EXPECT_TRUE("        \
                      << #expr << ") at line " << __LINE__ << '\n';       \
            std::exit(EXIT_FAILURE);                                        \
        }                                                                    \
    } while (false)

#define EXPECT_FALSE(expr) EXPECT_TRUE(!(expr))
#define EXPECT_EQ(actual, expected) EXPECT_TRUE((actual) == (expected))

void TestConstructor()
{
    std::cout << "\n========== TestConstructor ==========\n";

    FIFO<int> int_fifo(5);
    FIFO<float> float_fifo(4);
    FIFO<char> char_fifo(3);
    FIFO<std::string> string_fifo(2);

    EXPECT_EQ(int_fifo.Capacity(), 5U);
    EXPECT_EQ(float_fifo.Capacity(), 4U);
    EXPECT_EQ(char_fifo.Capacity(), 3U);
    EXPECT_EQ(string_fifo.Capacity(), 2U);
    EXPECT_TRUE(int_fifo.IsEmpty());
    EXPECT_FALSE(string_fifo.IsFull());

    std::cout << "[PASS] TestConstructor\n";
}

void TestZeroCapacity()
{
    std::cout << "\n========== TestZeroCapacity ==========\n";

    try
    {
        FIFO<int> fifo(0);
        (void)fifo;
        EXPECT_TRUE(false);
    }
    catch (const std::invalid_argument&)
    {
        std::cout << "[PASS] TestZeroCapacity\n";
    }
}

void TestPush()
{
    std::cout << "\n========== TestPush ==========\n";

    FIFO<int> int_fifo(2);
    EXPECT_TRUE(int_fifo.Push(10));
    EXPECT_TRUE(int_fifo.Push(20));
    EXPECT_TRUE(int_fifo.IsFull());
    EXPECT_FALSE(int_fifo.Push(30));

    FIFO<float> float_fifo(2);
    EXPECT_TRUE(float_fifo.Push(1.5F));
    EXPECT_TRUE(float_fifo.Push(2.5F));
    EXPECT_FALSE(float_fifo.Push(3.5F));

    FIFO<char> char_fifo(2);
    EXPECT_TRUE(char_fifo.Push('A'));
    EXPECT_TRUE(char_fifo.Push('B'));

    FIFO<std::string> string_fifo(2);
    EXPECT_TRUE(string_fifo.Push("first"));
    EXPECT_TRUE(string_fifo.Push("second"));
    EXPECT_FALSE(string_fifo.Push("third"));

    std::cout << "[PASS] TestPush\n";
}

void TestPop()
{
    std::cout << "\n========== TestPop ==========\n";

    FIFO<int> int_fifo(2);
    int_fifo.Push(10);
    int_fifo.Push(20);
    int int_value = 0;
    EXPECT_TRUE(int_fifo.Pop(int_value));
    EXPECT_EQ(int_value, 10);
    EXPECT_TRUE(int_fifo.Pop(int_value));
    EXPECT_EQ(int_value, 20);
    EXPECT_FALSE(int_fifo.Pop(int_value));

    FIFO<float> float_fifo(1);
    float_fifo.Push(1.25F);
    float float_value = 0.0F;
    EXPECT_TRUE(float_fifo.Pop(float_value));
    EXPECT_EQ(float_value, 1.25F);

    FIFO<char> char_fifo(1);
    char_fifo.Push('Z');
    char char_value = '\0';
    EXPECT_TRUE(char_fifo.Pop(char_value));
    EXPECT_EQ(char_value, 'Z');

    FIFO<std::string> string_fifo(1);
    string_fifo.Push("template");
    std::string string_value;
    EXPECT_TRUE(string_fifo.Pop(string_value));
    EXPECT_EQ(string_value, "template");

    std::cout << "[PASS] TestPop\n";
}

void TestClear()
{
    std::cout << "\n========== TestClear ==========\n";

    FIFO<int> int_fifo(3);
    int_fifo.Push(1);
    int_fifo.Push(2);
    int_fifo.Clear();
    EXPECT_TRUE(int_fifo.IsEmpty());
    EXPECT_EQ(int_fifo.Size(), 0U);
    EXPECT_TRUE(int_fifo.Push(3));

    FIFO<std::string> string_fifo(2);
    string_fifo.Push("one");
    string_fifo.Push("two");
    string_fifo.Clear();
    EXPECT_TRUE(string_fifo.IsEmpty());
    EXPECT_TRUE(string_fifo.Push("reused"));

    std::cout << "[PASS] TestClear\n";
}

void TestWrapAround()
{
    std::cout << "\n========== TestWrapAround ==========\n";

    FIFO<int> int_fifo(3);
    int value = 0;
    int_fifo.Push(1);
    int_fifo.Push(2);
    int_fifo.Push(3);
    int_fifo.Pop(value);
    int_fifo.Pop(value);
    int_fifo.Push(4);
    int_fifo.Push(5);
    EXPECT_TRUE(int_fifo.Pop(value));
    EXPECT_EQ(value, 3);
    EXPECT_TRUE(int_fifo.Pop(value));
    EXPECT_EQ(value, 4);
    EXPECT_TRUE(int_fifo.Pop(value));
    EXPECT_EQ(value, 5);

    FIFO<std::string> string_fifo(2);
    std::string value_string;
    string_fifo.Push("A");
    string_fifo.Push("B");
    string_fifo.Pop(value_string);
    string_fifo.Push("C");
    EXPECT_TRUE(string_fifo.Pop(value_string));
    EXPECT_EQ(value_string, "B");
    EXPECT_TRUE(string_fifo.Pop(value_string));
    EXPECT_EQ(value_string, "C");

    std::cout << "[PASS] TestWrapAround\n";
}

void TestDebugPrint()
{
    std::cout << "\n========== TestDebugPrint ==========\n";

    FIFO<int> int_fifo(2);
    int_fifo.Push(11);
    int_fifo.DebugPrint();

    FIFO<float> float_fifo(2);
    float_fifo.Push(1.5F);
    float_fifo.DebugPrint();

    FIFO<char> char_fifo(2);
    char_fifo.Push('X');
    char_fifo.DebugPrint();

    FIFO<std::string> string_fifo(2);
    string_fifo.Push("FIFO");
    string_fifo.DebugPrint();

    std::cout << "[PASS] TestDebugPrint\n";
}

void RunAllTests()
{
    std::cout << "========== FIFO TEMPLATE UNIT TEST ==========\n";

    TestConstructor();
    TestZeroCapacity();
    TestPush();
    TestPop();
    TestClear();
    TestWrapAround();
    TestDebugPrint();

    std::cout << "\n=============================================\n";
    std::cout << " ALL UNIT TESTS PASSED\n";
    std::cout << "=============================================\n";
}
