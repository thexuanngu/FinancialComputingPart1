#ifndef _COMPLEX_NUMBER_H__
#define _COMPLEX_NUMBER_H__

#include <iostream>

class ComplexNumber
{
public:

    // Constructors
    ComplexNumber(); // Already defined!
    explicit ComplexNumber(double , double=0.0); // Already defined!

    // += Complex Number
    ComplexNumber & operator+=(const ComplexNumber &); // Already defined!
    ComplexNumber & operator-=(const ComplexNumber &); // !
    ComplexNumber & operator*=(const ComplexNumber &); // !
    ComplexNumber & operator/=(const ComplexNumber &); // !

    // += Real Numbers
    ComplexNumber & operator+=(const double &); // !
    ComplexNumber & operator-=(const double &); // !
    ComplexNumber & operator*=(const double &); // !
    ComplexNumber & operator/=(const double &); // !

    // Print statement
    std::ostream & print(std::ostream &) const; // Already defined!

private:
    double dRe_;
    double dIm_;
};

// Binary operators Complex + Complex
ComplexNumber operator+(const ComplexNumber &,const ComplexNumber &); // Already defined!
ComplexNumber operator-(const ComplexNumber &,const ComplexNumber &); // !
ComplexNumber operator*(const ComplexNumber &,const ComplexNumber &); // !
ComplexNumber operator/(const ComplexNumber &,const ComplexNumber &); // !

// Binary operators Complex + Real
ComplexNumber operator+(const ComplexNumber &,const double &); // !
ComplexNumber operator-(const ComplexNumber &,const double &); // !
ComplexNumber operator*(const ComplexNumber &,const double &); // !
ComplexNumber operator/(const ComplexNumber &,const double &); // !

// Binary operators Real + Complex
ComplexNumber operator+(const double &,const ComplexNumber &); // !
ComplexNumber operator-(const double &,const ComplexNumber &); // !
ComplexNumber operator*(const double &,const ComplexNumber &); // !
ComplexNumber operator/(const double &,const ComplexNumber &); // !

// "Print" statement using std::cout << my_complex_number;
std::ostream & operator<<(std::ostream &, const ComplexNumber &); // Already defined!
//...
#endif //_COMPLEX_NUMBER_H__
