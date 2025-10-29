#include "fp.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

using cpp_example::fp::FieldParam;
using cpp_example::fp::Fp;

namespace {

unsigned int to_uint(const Fp &value) {
    return static_cast<unsigned int>(mpz_get_ui(value.raw()));
}

class FpTest : public ::testing::Test {
protected:
    FieldParam param{17u};
};

} // namespace

TEST_F(FpTest, Add) {
    Fp a(5u);
    Fp b(9u);
    Fp sum = Fp::add(a, b, param);
    EXPECT_EQ(14u, to_uint(sum));
}

TEST_F(FpTest, Sub) {
    Fp a(5u);
    Fp b(9u);
    Fp diff = Fp::sub(a, b, param);
    EXPECT_EQ(13u, to_uint(diff));
}

TEST_F(FpTest, Mul) {
    Fp a(5u);
    Fp b(9u);
    Fp prod = Fp::mul(a, b, param);
    EXPECT_EQ(11u, to_uint(prod));
}

TEST_F(FpTest, InverseExists) {
    Fp b(9u);
    Fp inv_b = Fp::inv(b, param);
    EXPECT_EQ(2u, to_uint(inv_b));

    Fp identity = Fp::mul(b, inv_b, param);
    EXPECT_EQ(1u, to_uint(identity));
}

TEST_F(FpTest, InverseThrowsIfNotInvertible) {
    Fp zero(0u);
    EXPECT_THROW(Fp::inv(zero, param), std::invalid_argument);
}
