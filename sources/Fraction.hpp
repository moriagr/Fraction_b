#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
namespace ariel
{
    class Fraction
    {
    private:
        int numerator;
        int denominator;

    public:
        // Copy constructor
        Fraction(float other);

        // Assignment operator
        Fraction &operator=(const Fraction &other);

        Fraction(int numerator, int denominator);

        Fraction();
        ~Fraction();
        // Copy constructor
        Fraction(const Fraction &other);

        // Move assignment operator
        Fraction &operator=(Fraction &&other) noexcept;

        // Move constructor
        Fraction(Fraction &&other) noexcept;

        int getDenominator() const;
        int getNumerator() const;

        void setDenominator(int denominator);
        void setNumerator(int numerator);

        friend Fraction operator*(const Fraction &fraction1, const Fraction &fraction2);

        friend Fraction operator/(const Fraction &fraction1, const Fraction &fraction2);

        friend Fraction operator-(const Fraction &fraction1, const Fraction &fraction2);

        friend Fraction operator+(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator==(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator!=(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator<(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator>(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator<=(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator>=(const Fraction &fraction1, const Fraction &fraction2);

        Fraction operator++();    // pre-decrement
        Fraction operator++(int); // post-increment
        Fraction operator--();    // pre-decrement
        Fraction operator--(int); // post-decrement
        friend std::ostream &operator<<(std::ostream &output, const Fraction &fraction);
        friend std::istream &operator>>(std::istream &input, Fraction &fraction);
        friend Fraction &operator>>(Fraction &fraction1, Fraction &fraction2);
    };
}