#include "fp.hpp"

#include <stdexcept>

namespace cpp_example::fp {

FieldParam::FieldParam() {
    mpz_init(prime_);
}

FieldParam::FieldParam(unsigned int v) {
    mpz_init_set_ui(prime_, v);
}

FieldParam::FieldParam(const FieldParam &other) {
    mpz_init_set(prime_, other.prime_);
}

FieldParam::FieldParam(FieldParam &&other) noexcept {
    mpz_init(prime_);
    mpz_swap(prime_, other.prime_);
}

FieldParam &FieldParam::operator=(const FieldParam &other) {
    if (this != &other) {
        mpz_set(prime_, other.prime_);
    }
    return *this;
}

FieldParam &FieldParam::operator=(FieldParam &&other) noexcept {
    if (this != &other) {
        mpz_swap(prime_, other.prime_);
    }
    return *this;
}

FieldParam::~FieldParam() {
    mpz_clear(prime_);
}

Fp::Fp() {
    mpz_init(value_); // mpz_init defaults to zero
}

Fp::Fp(unsigned int v) {
    mpz_init_set_ui(value_, v);
}

Fp::Fp(const Fp &other) {
    mpz_init_set(value_, other.value_);
}

Fp::Fp(Fp &&other) noexcept {
    mpz_init(value_);
    mpz_swap(value_, other.value_);
}

Fp &Fp::operator=(const Fp &other) {
    if (this != &other) {
        mpz_set(value_, other.value_);
    }
    return *this;
}

Fp &Fp::operator=(Fp &&other) noexcept {
    if (this != &other) {
        mpz_swap(value_, other.value_);
    }
    return *this;
}

Fp::~Fp() {
    mpz_clear(value_);
}

Fp Fp::add(const Fp &a, const Fp &b, const FieldParam &p) {
    Fp result;
    mpz_add(result.value_, a.value_, b.value_);
    mpz_mod(result.value_, result.value_, p.prime());
    return result;
}

Fp Fp::sub(const Fp &a, const Fp &b, const FieldParam &p) {
    Fp result;
    mpz_sub(result.value_, a.value_, b.value_);
    mpz_mod(result.value_, result.value_, p.prime());
    return result;
}

Fp Fp::mul(const Fp &a, const Fp &b, const FieldParam &p) {
    Fp result;
    mpz_mul(result.value_, a.value_, b.value_);
    mpz_mod(result.value_, result.value_, p.prime());
    return result;
}

Fp Fp::inv(const Fp &a, const FieldParam &p) {
    Fp result;
    if (mpz_invert(result.value_, a.value_, p.prime()) == 0) {
        throw std::invalid_argument("multiplicative inverse does not exist for the given element");
    }
    return result;
}

} // namespace cpp_example::fp
