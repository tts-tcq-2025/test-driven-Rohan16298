#include "stringcalculator.h"

#include <cstdio>
#include <string>

#include <gtest/gtest.h>

class StringCalculatorTest : public ::testing::Test {
 protected:
    StringCalculator calculator;
};

TEST_F(StringCalculatorTest, EmptyStringReturnsZero) {
    EXPECT_EQ(calculator.Add(""), 0);
}

TEST_F(StringCalculatorTest, SingleNumberReturnsValue) {
    EXPECT_EQ(calculator.Add("5"), 5);
}

TEST_F(StringCalculatorTest, TwoNumbersCommaDelimited) {
    EXPECT_EQ(calculator.Add("1,2"), 3);
}

TEST_F(StringCalculatorTest, TwoNumbersNewlineDelimited) {
    EXPECT_EQ(calculator.Add("1\n2"), 3);
}

TEST_F(StringCalculatorTest, ThreeNumbersDelimitedVariousWays) {
    EXPECT_EQ(calculator.Add("1\n2,3"), 6);
}

TEST_F(StringCalculatorTest, CustomDelimiter) {
    EXPECT_EQ(calculator.Add("//;\n1;2"), 3);
}

TEST_F(StringCalculatorTest, NegativeNumbersThrow) {
    try {
        calculator.Add("1,-2,3,-4");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument &e) {
        std::string msg = e.what();
        EXPECT_NE(msg.find("negatives not allowed"), std::string::npos);
        EXPECT_NE(msg.find("-2"), std::string::npos);
        EXPECT_NE(msg.find("-4"), std::string::npos);
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST_F(StringCalculatorTest, NumbersGreaterThan1000Ignored) {
    EXPECT_EQ(calculator.Add("2,1001"), 2);
}
