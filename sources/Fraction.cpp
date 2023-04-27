#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "Fraction.hpp"
namespace ariel
{

    Fraction::Fraction()
    {
        this->numerator = 0;
        this->denominator = 1;
    }

    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
    {
    }

    Fraction::Fraction(float other)
    {
        this->numerator = other * 1000;
        this->denominator = 1000;
    }
    Fraction::Fraction(const Fraction &other)
    {
        Fraction(other.numerator, other.denominator);
    }
    int Fraction::getDenominator() const
    {
        return denominator;
    }
    int Fraction::getNumerator() const
    {
        return numerator;
    }

    // Move constructor
    Fraction::Fraction(Fraction &&other) noexcept : numerator(other.numerator), denominator(other.denominator)
    {
        // Move constructor: take ownership of the resources of the other object
        other.numerator = 0;
        other.denominator = 1;
    }
    Fraction &Fraction::operator=(const Fraction &other)
    {
        return *this;
    }

    Fraction &Fraction::operator=(Fraction &&other) noexcept
    {
        return *this;
    }
    Fraction::~Fraction()
    {
    }

    Fraction Fraction::operator++()
    {
        return Fraction(numerator, denominator);
    }

    Fraction Fraction::operator++(int)
    {
        return Fraction(numerator, denominator);
    }
    // pre-decrement
    Fraction Fraction::operator--()
    {
        return Fraction(numerator, denominator);
    }

    // post-decrement
    Fraction Fraction::operator--(int)
    {
        return Fraction(numerator, denominator);
    }

    std::ostream &operator<<(std::ostream &output, const Fraction &fraction)
    {
        return (output << fraction.getNumerator() << '/' << fraction.getDenominator());
    }

    Fraction operator>>(std::istream &input, const Fraction &fraction)
    {

        return fraction;
    }
    Fraction operator*(const Fraction &fraction1, const Fraction &fraction2)
    {
        return fraction1;
    }

    Fraction operator/(const Fraction &fraction1, const Fraction &fraction2)
    {
        return fraction1;
    }

    Fraction operator+(const Fraction &fraction1, const Fraction &fraction2)
    {
        return fraction1;
    }

    Fraction operator-(const Fraction &fraction1, const Fraction &fraction2)
    {
        return fraction1;
    }

    bool operator==(const Fraction &fraction1, const Fraction &fraction2)
    {
        return false;
    }

    bool operator!=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return false;
    }

    bool operator<(const Fraction &fraction1, const Fraction &fraction2)
    {
        return false;
    }

    bool operator>(const Fraction &fraction1, const Fraction &fraction2)
    {
        return false;
    }

    bool operator<=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return false;
    }

    bool operator>=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return false;
    }
}