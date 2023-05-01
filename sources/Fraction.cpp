#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <algorithm> // For __gcd; taken from the internet
#include <typeinfo>  // For typeid(...)
#include <iomanip>

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
        int gcd_diff = __gcd((int)(other * 1000), 1000);
        this->numerator = (other * 1000) / gcd_diff;
        this->denominator = 1000 / gcd_diff;
    }
    Fraction::Fraction(const Fraction &other)
    {
        int gcd_diff = __gcd(other.getNumerator(), other.getDenominator());
        // printf("%d:  ", gcd_diff);
        this->numerator = other.getNumerator() / gcd_diff;

        this->denominator = other.getDenominator() / gcd_diff;
        if (this->denominator < 0)
        {
            this->denominator = this->denominator * -1;
            this->numerator = this->numerator * -1;
        }
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
    Fraction &Fraction::operator=(const Fraction &other)
    {

        this->numerator = other.getNumerator();
        this->denominator = other.getDenominator();
        int gcd_diff = __gcd(this->numerator, this->denominator);
        this->numerator = this->numerator / gcd_diff;
        this->denominator = this->denominator / gcd_diff;
        return *this;
    }

    Fraction &Fraction::operator=(Fraction &&other) noexcept
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
        int num = fraction.getNumerator();
        int den = fraction.getDenominator();
        if (den < 0)
        {
            num = num * -1;
            den = den * -1;
        }
        return (output << num << '/' << den);
    }

    std::istream &operator>>(std::istream &input, Fraction &fraction)
    {
        float num, den;
        char slash;
        input >> num;
        // char* vf = input.
        if (input.fail())
        {
            return input;
        }

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
        else if (input.peek() == '.')
        {
            throw std::runtime_error("can't have float numerator in input");
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
            if (input.peek() == -1)
            {
                throw std::runtime_error("Something wrong ");
            }
            throw std::logic_error("Trying to add fraction which isn't in the correct format");
        }
        if (den == 0)
        {
            throw std::runtime_error("can't have denominator zero");
        }
        int num1 = num;
        int den1 = den;
        if (num != num1 || den != den1)
        {
            throw std::runtime_error("can't have float numerator in input");
        }
        if (den1 < 0)
        {
            den1 = den1 * -1;
            num1 = num * -1;
        }
        
        cout << num1 << "/" << den1 << endl;
        cout << input.peek() << endl;
        cout << slash << endl;
        fraction.setNumerator(num1);
        fraction.setDenominator(den1);

        return input;
    }

    // bool overflow_fun(const Fraction &fraction){
    //     long

    // }

    // Fraction &operator>>(Fraction &fraction1, Fraction &fraction2)
    // {
    //     cout << fraction1 << endl;
    //     cout << fraction2 << endl;
    //     if (fraction1.getDenominator() == 0)
    //     {
    //         throw std::runtime_error("can't have denominator zero");
    //     }
    //     fraction2.setNumerator(fraction1.getNumerator());
    //     fraction2.setDenominator(fraction1.getDenominator());
    //     if (fraction2.getDenominator() == 0)
    //     {
    //         throw std::runtime_error("can't have denominator zero");
    //     }
    //     return fraction1;
    // }

    Fraction
    operator*(const Fraction &fraction1, const Fraction &fraction2)
    {

        int max_int = std::numeric_limits<int>::max();
        int min_int = std::numeric_limits<int>::min();

        cout << fraction1 << endl;
        cout << fraction2 << endl;
        if (fraction1.getNumerator() == 1 && fraction1.getDenominator() == 1)
        {
            return fraction2;
        }
        if (fraction2.getNumerator() == 1 && fraction2.getDenominator() == 1)
        {
            return fraction1;
        }
        if (fraction1.getNumerator() >= max_int || fraction1.getNumerator() <= min_int ||
            fraction2.getNumerator() >= max_int || fraction2.getNumerator() <= min_int ||
            fraction1.getDenominator() >= max_int || fraction1.getDenominator() <= min_int ||
            fraction2.getDenominator() >= max_int || fraction2.getDenominator() <= min_int)
        {
            throw std::overflow_error("td::numeric_limits");
        }
        long num = fraction1.getNumerator() * fraction2.getNumerator();
        long den = fraction1.getDenominator() * fraction2.getDenominator();

        int gcd_diff = __gcd(num, den);

        if (num / gcd_diff >= max_int || num / gcd_diff <= min_int || den / gcd_diff >= max_int || den / gcd_diff <= min_int)
        {
            throw std::overflow_error("td::numeric_limits");
        }

        return Fraction(num / gcd_diff, den / gcd_diff);
    }

    Fraction operator/(const Fraction &fraction1, const Fraction &fraction2)
    {
        if (fraction2.getNumerator() == 1 && fraction2.getDenominator() == 1)
        {
            return fraction1;
        }
        if (fraction1.getDenominator() == 0 || fraction2.getDenominator() == 0 || fraction2.getNumerator() == 0)
        {
            throw std::runtime_error("denominator can't be zero");
        }

        int max_int = std::numeric_limits<int>::max();
        int min_int = std::numeric_limits<int>::min();
        if (fraction1.getNumerator() >= max_int || fraction1.getNumerator() <= min_int ||
            fraction2.getNumerator() >= max_int || fraction2.getNumerator() <= min_int ||
            fraction1.getDenominator() >= max_int || fraction1.getDenominator() <= min_int ||
            fraction2.getDenominator() >= max_int || fraction2.getDenominator() <= min_int)
        {
            throw std::overflow_error("td::numeric_limits");
        }
        long num = fraction1.getNumerator() * fraction2.getDenominator();
        long den = fraction1.getDenominator() * fraction2.getNumerator();
        int gcd_diff = __gcd(num, den);
        if (num / gcd_diff >= max_int || num / gcd_diff <= min_int || den / gcd_diff >= max_int || den / gcd_diff <= min_int)
        {
            throw std::overflow_error("td::numeric_limits");
        }
        return Fraction(num / gcd_diff, den / gcd_diff);
    }

    Fraction operator+(const Fraction &fraction1, const Fraction &fraction2)
    {
        int max_int = std::numeric_limits<int>::max();
        int min_int = std::numeric_limits<int>::min();
        if (fraction1.getNumerator() >= max_int || fraction1.getNumerator() <= min_int ||
            fraction2.getNumerator() >= max_int || fraction2.getNumerator() <= min_int ||
            fraction1.getDenominator() >= max_int || fraction1.getDenominator() <= min_int ||
            fraction2.getDenominator() >= max_int || fraction2.getDenominator() <= min_int)
        {
            throw std::overflow_error("td::numeric_limits");
        }
        long num = fraction1.getNumerator() * fraction2.getDenominator() + fraction2.getNumerator() * fraction1.getDenominator();
        long den = fraction1.getDenominator() * fraction2.getDenominator();
        int gcd_diff = __gcd(num, den);

        if (num / gcd_diff >= max_int || num / gcd_diff <= min_int || den / gcd_diff >= max_int || den / gcd_diff <= min_int)
        {
            throw std::overflow_error("td::numeric_limits");
        }
        return Fraction(num / gcd_diff, den / gcd_diff);
    }

    Fraction operator-(const Fraction &fraction1, const Fraction &fraction2)
    {
        int max_int = std::numeric_limits<int>::max();
        int min_int = std::numeric_limits<int>::min();
        if (fraction1.getNumerator() >= max_int || fraction1.getNumerator() <= min_int ||
            fraction2.getNumerator() >= max_int || fraction2.getNumerator() <= min_int ||
            fraction1.getDenominator() >= max_int || fraction1.getDenominator() <= min_int ||
            fraction2.getDenominator() >= max_int || fraction2.getDenominator() <= min_int)
        {
            throw std::overflow_error("td::numeric_limits");
        }
        long num = fraction1.getNumerator() * fraction2.getDenominator() - fraction2.getNumerator() * fraction1.getDenominator();
        long den = fraction1.getDenominator() * fraction2.getDenominator();
        int gcd_diff = __gcd(num, den);

        if (num / gcd_diff >= max_int || num / gcd_diff <= min_int || den / gcd_diff >= max_int || den / gcd_diff <= min_int)
        {
            throw std::overflow_error("td::numeric_limits");
        }

        return Fraction(num / gcd_diff, den / gcd_diff);
    }

    float transform2Float(const Fraction &fraction)
    {
        if (fraction.getDenominator() == 0)
        {
            throw std::runtime_error("denominator can't be zero");
        }
        float f1 = (float)fraction.getNumerator() / (float)fraction.getDenominator();

        std::stringstream stream;
        stream << std::fixed << std::setprecision(3) << f1;
        float new_f1;
        stream >> new_f1;
        return new_f1;
    }

    bool operator==(const Fraction &fraction1, const Fraction &fraction2)
    {
        float num1 = transform2Float(fraction1);
        float num2 = transform2Float(fraction2);
        // int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        // int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 == num2)
        {
            return true;
        }
        return false;
    }

    bool operator!=(const Fraction &fraction1, const Fraction &fraction2)
    {
        float num1 = transform2Float(fraction1);
        float num2 = transform2Float(fraction2);
        // int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        // int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 != num2)
        {
            return true;
        }
        return false;
    }

    bool operator<(const Fraction &fraction1, const Fraction &fraction2)
    {
        float num1 = transform2Float(fraction1);
        float num2 = transform2Float(fraction2);
        // int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        // int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 < num2)
        {
            return true;
        }
        return false;
    }

    bool operator>(const Fraction &fraction1, const Fraction &fraction2)
    {
        float num1 = transform2Float(fraction1);
        float num2 = transform2Float(fraction2);
        // int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        // int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        if (num1 > num2)
        {
            return true;
        }
        return false;
    }

    bool operator<=(const Fraction &fraction1, const Fraction &fraction2)
    {
        // int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        // int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        // if ((fraction1.getNumerator() < 0 || fraction1.getDenominator() < 0) && (fraction2.getNumerator() > 0 || fraction2.getDenominator() > 0))
        // {
        //     return true;
        // }
        // if ((fraction2.getNumerator() < 0 || fraction2.getDenominator() < 0) && (fraction1.getNumerator() > 0 || fraction1.getDenominator() > 0))
        // {
        //     return false;
        // }
        float num1 = transform2Float(fraction1);
        float num2 = transform2Float(fraction2);

        if (num1 < num2 || num1 == num2)
        {
            return true;
        }
        return false;
    }

    bool operator>=(const Fraction &fraction1, const Fraction &fraction2)
    {
        // int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        // int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        // if ((fraction1.getNumerator() < 0 || fraction1.getDenominator() < 0) && (fraction2.getNumerator() > 0 || fraction2.getDenominator() > 0))
        // {
        //     return false;
        // }
        // if ((fraction2.getNumerator() < 0 || fraction2.getDenominator() < 0) && (fraction1.getNumerator() > 0 || fraction1.getDenominator() > 0))
        // {
        //     return true;
        // }
        float num1 = transform2Float(fraction1);
        float num2 = transform2Float(fraction2);
        if (num1 > num2 || num1 == num2)
        {
            return true;
        }
        return false;
    }
}

//  float f1 = (double)fraction1.getNumerator() / (double)fraction1.getDenominator();
//         float f2 = (double)fraction2.getNumerator() / (double)fraction2.getDenominator();

//         std::stringstream stream_f1;
//         stream_f1 << std::fixed << std::setprecision(3) << f1;
//         float new_f1;
//         stream_f1 >> new_f1;

//         std::stringstream stream_f2;
//         stream_f2 << std::fixed << std::setprecision(3) << f2;
//         float new_f2;
//         stream_f2 >> new_f2;
//         float sum = new_f1 - new_f2;

//         std::stringstream stream_f3;

//         stream_f3 << std::fixed << std::setprecision(3) << sum;
//         float new_f3;
//         stream_f3 >> new_f3;

// if (fraction1.getDenominator() == 0 || fraction2.getDenominator() == 0 || fraction2.getNumerator() == 0)
//         {
//             throw std::runtime_error("denominator can't be zero");
//         }

//         float f1 = (double)fraction1.getNumerator() / (double)fraction1.getDenominator();
//         float f2 = (double)fraction2.getNumerator() / (double)fraction2.getDenominator();

//         std::stringstream stream_f1;
//         stream_f1 << std::fixed << std::setprecision(3) << f1;
//         float new_f1;
//         stream_f1 >> new_f1;

//         std::stringstream stream_f2;
//         stream_f2 << std::fixed << std::setprecision(3) << f2;
//         float new_f2;
//         stream_f2 >> new_f2;
//         float div = new_f1 / new_f2;

//         std::stringstream stream_f3;

//         stream_f3 << std::fixed << std::setprecision(3) << div;
//         float new_f3;
//         stream_f3 >> new_f3;