#pragma once

#include <gmp.h>

namespace cpp_example::fp {

class FieldParam {
public:
    FieldParam();
    explicit FieldParam(unsigned int);
    FieldParam(const FieldParam &);
    FieldParam(FieldParam &&) noexcept;
    FieldParam &operator=(const FieldParam &);
    FieldParam &operator=(FieldParam &&) noexcept;
    ~FieldParam();

    const mpz_t &prime() const {
        return prime_;
    }

private:
    mpz_t prime_;
};

// Thin RAII wrapper around GMP's mpz_t for natural numbers.
class Fp {
public:
    Fp();                      // zero-initialized
    explicit Fp(unsigned int); // initialize from small unsigned value
    Fp(const Fp &);
    Fp(Fp &&) noexcept;
    Fp &operator=(const Fp &);
    Fp &operator=(Fp &&) noexcept;
    ~Fp();

    const mpz_t &raw() const {
        return value_;
    }

    static Fp add(const Fp &, const Fp &, const FieldParam &);
    static Fp sub(const Fp &, const Fp &, const FieldParam &);
    static Fp mul(const Fp &, const Fp &, const FieldParam &);
    static Fp inv(const Fp &, const FieldParam &);

private:
    mpz_t value_;
};

} // namespace cpp_example::fp
