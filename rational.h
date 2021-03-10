#include <numeric>

using namespace std;

class Rational {
    int numerator;
    int denominator;

public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    explicit Rational(int num) {
        numerator = num;
        denominator = 1;
    }

    Rational(int num, int denom) {
        numerator = num * (denom > 0 ? 1 : -1);
        denominator = denom * (denom > 0 ? 1 : -1);
        Reduce();
    }

    void Reduce() {
        int num_denom_gcd = gcd(numerator, denominator);
        numerator /= num_denom_gcd;
        denominator /= num_denom_gcd;
        numerator = numerator * (denominator > 0 ? 1 : -1);
        denominator = denominator * (denominator > 0 ? 1 : -1);
    }

    Rational& operator += (const Rational& rhs) {
        numerator = numerator * rhs.Denominator()
                    + rhs.Numerator() * denominator;
        denominator = denominator * rhs.denominator;
        Reduce();
        return *this;
    }

    Rational& operator += (int rhs) {
        numerator += rhs * denominator;
        return *this;
    }

    friend Rational operator += (int lhs, const Rational& rhs) {
        return Rational(rhs.numerator + lhs * rhs.denominator, rhs.denominator);
    }

    template<typename T1, typename T2>
    friend Rational operator + (T1 lhs, const T2& rhs) {
        return lhs += rhs;
    }

    Rational& operator -= (const Rational& rhs) {
        numerator = numerator * rhs.Denominator()
                    - rhs.Numerator() * denominator;
        denominator = denominator * rhs.denominator;
        Reduce();
        return *this;
    }

    Rational& operator -= (int rhs) {
        numerator -= rhs * denominator;
        return *this;
    }

    friend Rational operator -= (int lhs, const Rational& rhs) {
        return Rational(lhs * rhs.denominator - rhs.numerator, rhs.denominator);
    }

    template<typename T1, typename T2>
    friend Rational operator - (T1 lhs, const T2& rhs) {
        return lhs -= rhs;
    }

    Rational& operator *= (const Rational& rhs) {
        numerator *= rhs.numerator;
        denominator *= rhs.denominator;
        Reduce();
        return *this;
    }

    Rational& operator *= (int rhs) {
        numerator *= rhs;
        Reduce();
        return *this;
    }

    friend Rational operator *= (int lhs, const Rational& rhs) {
        Rational res = Rational(rhs.numerator * lhs, rhs.denominator);
        res.Reduce();
        return res;
    }

    template<typename T1, typename T2>
    friend Rational operator * (T1 lhs, const T2& rhs) {
        return lhs *= rhs;
    }

    Rational& operator /= (const Rational rhs) {
        numerator *= rhs.denominator;
        denominator *= rhs.numerator;
        Reduce();
        return *this;
    }

    Rational& operator /= (int rhs) {
        denominator *= rhs;
        Reduce();
        return *this;
    }

    friend Rational operator /= (int lhs, const Rational& rhs) {
        Rational res = Rational(lhs * rhs.denominator, rhs.numerator);
        res.Reduce();
        return res;
    }

    template<typename T1, typename T2>
    friend Rational operator / (T1 lhs, const T2& rhs) {
        return lhs /= rhs;
    }

    bool operator == (const Rational& rhs) const {
        return numerator == rhs.numerator && denominator == rhs.denominator;
    }

    bool operator != (const Rational& rhs) const {
        return !(*this == rhs);
    }

    Rational& operator++() {
        numerator += denominator;
        return *this;
    }

    Rational operator++(int) {
        Rational old = *this;
        operator++();
        return old;
    }

    Rational& operator--() {
        numerator -= denominator;
        return *this;
    }

    Rational operator--(int) {
        Rational old = *this;
        operator--();
        return old;
    }

    Rational operator + () {
        return *this;
    }

    Rational operator - () const {
        return Rational(-numerator, denominator);
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }
};
