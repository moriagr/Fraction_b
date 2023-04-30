#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits.h>
#include <algorithm> // For __gcd; taken from the internet
#include <typeinfo>  // For typeid(...)

using namespace std;

#include "Fraction.hpp"
namespace ariel
{

    Fraction::Fraction()
    {
        this->numerator = 0;
        this->denominator = 1;
    }

    Fraction::Fraction(int num, int den)
    {
        if (den == 0)
        {
            throw std::invalid_argument("denominator can't be zero");
        }
        int gcd_diff = __gcd(num, den);
        // printf("%d:  ", gcd_diff);
        this->numerator = num / gcd_diff;
        this->denominator = den / gcd_diff;
    }

    Fraction::Fraction(float other)
    {
        this->numerator = other * 1000;
        this->denominator = 1000;
    }
    Fraction::Fraction(const Fraction &other)
    {
        int gcd_diff = __gcd(other.getNumerator(), other.getDenominator());
        // printf("%d:  ", gcd_diff);
        this->numerator = other.getNumerator() / gcd_diff;
        this->denominator = other.getDenominator() / gcd_diff;
    }
    int Fraction::getDenominator() const
    {
        return denominator;
    }
    int Fraction::getNumerator() const
    {
        return numerator;
    }

    void Fraction::setDenominator(int denominator)
    {
        this->denominator = denominator;
    }
    void Fraction::setNumerator(int numerator)
    {
        this->numerator = numerator;
    }

    // Move constructor
    Fraction::Fraction(Fraction &&other) noexcept : numerator(other.numerator), denominator(other.denominator)
    {
        // Move constructor: take ownership of the resources of the other object
        other.numerator = 0;
        other.denominator = 1;
    }
    Fraction Fraction::operator=(const Fraction &other)
    {

        this->numerator = other.getNumerator();
        this->denominator = other.getDenominator();
        int gcd_diff = __gcd(this->numerator, this->denominator);
        this->numerator = this->numerator / gcd_diff;
        this->denominator = this->denominator / gcd_diff;
        return *this;
    }

    Fraction Fraction::operator=(Fraction &&other) noexcept
    {
        this->numerator = other.getNumerator();
        this->denominator = other.getDenominator();
        int gcd_diff = __gcd(this->numerator, this->denominator);
        this->numerator = this->numerator / gcd_diff;
        this->denominator = this->denominator / gcd_diff;

        return *this;
    }
    Fraction::~Fraction()
    {
    }

    // pre-decrement
    Fraction Fraction::operator++()
    {
        this->numerator += this->denominator;
        return *this;
    }

    // post-decrement
    Fraction Fraction::operator++(int)
    {
        Fraction copy(*this);
        this->numerator += this->denominator;
        return copy;
    }
    // pre-decrement
    Fraction Fraction::operator--()
    {
        this->numerator -= this->denominator;
        return *this;
    }

    // post-decrement
    Fraction Fraction::operator--(int)
    {
        Fraction copy(*this);
        this->numerator -= this->denominator;
        return copy;
    }

    std::ostream &operator<<(std::ostream &output, const Fraction &fraction)
    {
        return (output << fraction.getNumerator() << '/' << fraction.getDenominator());
    }

    Fraction &operator>>(std::istream &input, Fraction &fraction)
    {
        int num, den;
        char slash;
        input >> num;
        if (input.peek() == '/')
        {
            input >> slash >> den;
            if (isdigit(input.peek()))
            {
                input >> den;
            }
            else
            {
                throw std::logic_error("Trying to add fraction which isn't in the correct format");
            }
        }
        else if (isspace(input.peek()))
        {
            input >> slash;
            if (isdigit(slash))
            {
                den = slash - '0';
            }
            else if (isdigit(input.peek()))
            {
                input >> den;
            }
            else
            {
                throw std::logic_error("Trying to add fraction which isn't in the correct format");
            }
        }
        else if (isdigit(input.peek()))
        {
            input >> den;
        }
        else
        {
            throw std::logic_error("Trying to add fraction which isn't in the correct format");
        }
        fraction.setNumerator(num);
        fraction.setDenominator(den);
        return fraction;
    }

    Fraction &operator>>(Fraction &fraction1, Fraction &fraction2)
    {
        fraction1.setNumerator(fraction2.getNumerator());
        fraction1.setDenominator(fraction2.getDenominator());
        return fraction1;
    }

    Fraction operator*(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num = fraction1.getNumerator() * fraction2.getNumerator();
        int den = fraction1.getDenominator() * fraction2.getDenominator();
        int gcd_diff = __gcd(num, den);

        return Fraction(num / gcd_diff, den / gcd_diff);
    }

    Fraction operator/(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num = fraction1.getNumerator() * fraction2.getDenominator();
        int den = fraction1.getDenominator() * fraction2.getNumerator();
        int gcd_diff = __gcd(num, den);

        return Fraction(num / gcd_diff, den / gcd_diff);
    }

    Fraction operator+(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num = fraction1.getNumerator() * fraction2.getDenominator() + fraction2.getNumerator() * fraction1.getDenominator();
        int den = fraction1.getDenominator() * fraction2.getDenominator();
        int gcd_diff = __gcd(num, den);

        return Fraction(num / gcd_diff, den / gcd_diff);
    }

    Fraction operator-(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num = fraction1.getNumerator() * fraction2.getDenominator() - fraction2.getNumerator() * fraction1.getDenominator();
        int den = fraction1.getDenominator() * fraction2.getDenominator();
        int gcd_diff = __gcd(num, den);

        return Fraction(num / gcd_diff, den / gcd_diff);
    }

    bool operator==(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 == num2)
        {
            return true;
        }
        return false;
    }

    bool operator!=(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 != num2)
        {
            return true;
        }
        return false;
    }

    bool operator<(const Fraction &fraction1, const Fraction &fraction2)
    {

        int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 < num2)
        {
            return true;
        }
        return false;
    }

    bool operator>(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 > num2)
        {
            return true;
        }
        return false;
    }

    bool operator<=(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        int num2 = fraction2.getNumerator() * fraction1.getDenominator();

        if (num1 < num2 || num1 == num2)
        {
            return true;
        }
        return false;
    }

    bool operator>=(const Fraction &fraction1, const Fraction &fraction2)
    {
        int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 > num2 || num1 == num2)
        {
            return true;
        }
        return false;
    }
}