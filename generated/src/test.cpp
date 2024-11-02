//
// Created by stef on 10/27/24.
//

#include "../include/test.h"

class Calculator {
public:
    int Add(int a, int b) { return a + b; }
    int Subtract(int a, int b) { return a - b; }
    int Multiply(int a, int b) { return a * b; }
    double Divide(int a, int b) { if (b == 0) throw std::invalid_argument("Division by zero"); return static_cast<double>(a) / b; }
};

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calc; // Instance of Calculator

    void SetUp() override { /* Optional setup code */ }
    void TearDown() override { /* Optional cleanup code */ }
};

TEST_F(CalculatorTest, AdditionTest) {
    EXPECT_EQ(calc.Add(1, 2), 3);
    EXPECT_EQ(calc.Add(-1, -1), -2);
}

TEST_F(CalculatorTest, SubtractionTest) {
    EXPECT_EQ(calc.Subtract(5, 3), 2);
    EXPECT_EQ(calc.Subtract(0, 5), -5);
}

TEST_F(CalculatorTest, DivisionTest) {
    EXPECT_DOUBLE_EQ(calc.Divide(10, 2), 5.0);
    EXPECT_THROW(calc.Divide(1, 0), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}