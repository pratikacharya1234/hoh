#ifndef ROBUSTFRACTION_H
#define ROBUSTFRACTION_H

#include <cstdlib>
#include <iostream>
using namespace std;

class Fraction {   
    private:
    //TODO: Create the following in the private access modifier:
    //      int numerator
    //      int denominator
    int numerator;
    int denominator;

    int greatestCommonDivisor(int a, int b) {
        if (b == 0)
            return abs(a);
        return abs(greatestCommonDivisor(b, a % b));
    }

    void simplify() {
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }

        if (denominator == 0) {
            denominator = 1;
        }

        int gcd = greatestCommonDivisor(numerator, denominator);
        if (gcd != 0) {
            numerator /= gcd;
            denominator /= gcd;
        }
    }

    public:
    //TODO: Create a default constructor that takes no parameters and does not set any values
    //TODO: Create another constructor that takes two parameters: int numerator & int denominator
    //      set the former equal to numerator and the latter to denominator
    Fraction() : numerator(0), denominator(1) {}

    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (this->denominator == 0) {
            this->denominator = 1;
        }
        simplify();
    }

    //TODO: now overload the << operator. Remember, operator<< is a friend to the class. Pass ostream& out as
    //      the first parameter and Fraction& fraction as the second parameter
    //      
    //      If the fraction denominator == 1 then you will just need to out the numerator.
    //      If the numerator is larger than the denominator, then you will need to make it a mixed fraction.
    //      For example, 4/3 would be 1 and 1/3.
    //      If the numerator is less than the denominator then just out the numerator followed by '/' and then the
    //      denominator. Finally return out.
    friend ostream& operator<<(ostream& out, const Fraction& fraction) {
        if (fraction.denominator == 1) {
            out << fraction.numerator;
            return out;
        }

        int whole = fraction.numerator / fraction.denominator;
        int remainder = abs(fraction.numerator % fraction.denominator);

        if (abs(fraction.numerator) >= fraction.denominator && remainder != 0) {
            out << whole << " and " << remainder << "/" << fraction.denominator;
        } else {
            out << fraction.numerator << "/" << fraction.denominator;
        }
        return out;
    }

    friend istream& operator>>(istream& in, Fraction& fraction) {
        //TODO: Now we need to overload operator>>. This is also a friend to the class. Start by prompting
        //      the user to enter a fraction in the format of n/d
        //      You will then need to in the numerator, slash, and then the denominator
        //      If the denominator == 0 then tell the user that the denominator cannot be zero and
        //      set it to 1. Finally, return in
        char slash;
        in >> fraction.numerator >> slash >> fraction.denominator;

        if (!in || slash != '/') {
            in.setstate(ios::failbit);
            return in;
        }

        if (fraction.denominator == 0) {
            fraction.denominator = 1;
        }

        fraction.simplify();
        return in;
    }

    friend Fraction operator+(Fraction op1, Fraction op2) {
        //TODO: Now overload operator+. To do this, you need to use the following formula:
        //      a/b + c/d
        //      denominator = b * d
        //      numerator = (a * d) + (c * b)
        //      You will then need to make a new fraction object and pass in the new numerator and new
        //      denominator. Call the simplify() function on the new fraction object and then return it.
        int denominator = op1.denominator * op2.denominator;
        int numerator = (op1.numerator * op2.denominator) + (op2.numerator * op1.denominator);
        Fraction result(numerator, denominator);
        result.simplify();
        return result;
    }

    //TODO: We will now need to overload operator-. The set up will be similar the operator+ function.
    //      The formula will be the following:
    //      a/b - c/d
    //      denominator = a * d
    //      numerator = (a * d) - (c * b)
    //      You will once again need to call a fraction object and pass the new numerator and denominator
    //      Remember to call simplify() and return the new object.
    friend Fraction operator-(Fraction op1, Fraction op2) {
        int denominator = op1.denominator * op2.denominator;
        int numerator = (op1.numerator * op2.denominator) - (op2.numerator * op1.denominator);
        Fraction result(numerator, denominator);
        result.simplify();
        return result;
    }

    friend Fraction operator*(Fraction op1, Fraction op2) {
        //TODO: The formula for this one will be the following:
        //      a/b * c/d
        //      denominator = b * d
        //      numerator = a * c
        //      Call a new fraction object and pass the numerator and the denominator
        //      Simplify the fraction and return the object.
        int denominator = op1.denominator * op2.denominator;
        int numerator = op1.numerator * op2.numerator;
        Fraction result(numerator, denominator);
        result.simplify();
        return result;
    }

    //TODO: We will now overload the operator/. It will look similar to the function above.
    //      a/b / c/d
    //      denominator = b * c
    //      numerator = a * d
    //      Create a new fraction object and pass the numerator and the denominator and simplify the fraction
    //      return the new object
    friend Fraction operator/(Fraction op1, Fraction op2) {
        int denominator = op1.denominator * op2.numerator;
        int numerator = op1.numerator * op2.denominator;
        Fraction result(numerator, denominator);
        result.simplify();
        return result;
    }

    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

    Fraction& operator+=(Fraction fraction) {
        *this = *this + fraction;
        return *this;
    }

    Fraction& operator-=(Fraction fraction) {
        *this = *this - fraction;
        return *this;
    }

    Fraction& operator*=(Fraction fraction) {
        *this = *this * fraction;
        return *this;
    }

    Fraction& operator/=(Fraction fraction) {
        *this = *this / fraction;
        return *this;
    }

    Fraction& operator++() {
        numerator += denominator;
        simplify(); 
        return *this; 
    }

    Fraction operator++(int) {
        Fraction tmp(*this); 
        ++(*this); 
        return tmp;
    }

    Fraction& operator--() {
        numerator -= denominator;
        simplify(); 
        return *this;
    }

    Fraction operator--(int) {
        Fraction tmp(*this);
        --(*this);
        return tmp;
    }
};
#endif