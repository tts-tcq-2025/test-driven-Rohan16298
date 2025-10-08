#include <gtest/gtest.h>
#include "StringCalculator.h"

class StringCalculatorTest : public ::testing::Test
{
protected:
    StringCalculator calc;
};

TEST_F(StringCalculatorTest, EmptyStringReturnsZero)
{
    EXPECT_EQ(calc.Add(""), 0);
}

TEST_F(StringCalculatorTest, SingleNumberReturnsValue)
{
    EXPECT_EQ(calc.Add("5"), 5);
    EXPECT_EQ(calc.Add("0"), 0);
}

TEST_F(StringCalculatorTest, TwoNumbersCommaDelimited)
{
    EXPECT_EQ(calc.Add("1,2"), 3);
    EXPECT_EQ(calc.Add("10,20"), 30);
}

TEST_F(StringCalculatorTest, MultipleNumbersCommaDelimited)
{
    EXPECT_EQ(calc.Add("1,2,3,4,5"), 15);
}

TEST_F(StringCalculatorTest, NewLineDelimiterSupported)
{
    EXPECT_EQ(calc.Add("1\n2,3"), 6);
    EXPECT_EQ(calc.Add("4\n5\n6"), 15);
}

TEST_F(StringCalculatorTest, CustomSingleCharDelimiter)
{
    EXPECT_EQ(calc.Add("//;\n1;2"), 3);
    EXPECT_EQ(calc.Add("//#\n4#5#6"), 15);
}

TEST_F(StringCalculatorTest, CustomMultiCharDelimiter)
{
    EXPECT_EQ(calc.Add("//[***]\n1***2***3"), 6);
    EXPECT_EQ(calc.Add("//[abc]\n4abc5abc6"), 15);
}

TEST_F(StringCalculatorTest, MultipleCustomDelimiters)
{
    EXPECT_EQ(calc.Add("//[*][%]\n1*2%3"), 6);
    EXPECT_EQ(calc.Add("//[**][%%]\n4**5%%6"), 15);
}

TEST_F(StringCalculatorTest, NegativeNumbersThrowException)
{
    try
    {
        calc.Add("1,-2,3,-4");
        FAIL() << "Expected std::invalid_argument";
    }
    catch (const std::invalid_argument &e)
    {
        std::string msg = e.what();
        EXPECT_NE(msg.find("negatives not allowed"), std::string::npos);
        EXPECT_NE(msg.find("-2"), std::string::npos);
        EXPECT_NE(msg.find("-4"), std::string::npos);
    }
    catch (...)
    {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST_F(StringCalculatorTest, NumbersGreaterThan1000Ignored)
{
    EXPECT_EQ(calc.Add("2,1001"), 2);
    EXPECT_EQ(calc.Add("1000,1001,1002,3"), 1003);
}

TEST_F(StringCalculatorTest, InvalidInputThrowsException)
{
    EXPECT_THROW(calc.Add("1,\n"), std::invalid_argument);
    EXPECT_THROW(calc.Add("1,\n2"), std::invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
