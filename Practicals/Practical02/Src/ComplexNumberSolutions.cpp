#include "Practical02/ComplexNumber.hpp"

/* Incremental operators with complex numbers... */

ComplexNumber & ComplexNumber::operator+=(const ComplexNumber & cnArg)
{
    dRe_ += cnArg.dRe_;
    dIm_ += cnArg.dIm_;
    return *this;
}

// Decremental operators with complex numbers
ComplexNumber & ComplexNumber::operator-=(const ComplexNumber & cnArg)
{
	dRe_ -= cnArg.dRe_;
	dIm_ -= cnArg.dIm_;
	return *this;
}



// Incremental operators with real numbers
ComplexNumber & ComplexNumber::operator+=(const double & value) {
    dRe_ += value;
    return *this;
}

ComplexNumber operator+(const ComplexNumber & Arg1,
            const ComplexNumber & Arg2)
{
    ComplexNumber Res(Arg1);
    return Res +=Arg2;
}


// Binary operators Complex + Complex
ComplexNumber operator-(const ComplexNumber & Arg1,
            const ComplexNumber & Arg2)
{
    ComplexNumber Res(Arg1);
    return Res -=Arg2;
}

// Binary operators Complex + Real
ComplexNumber operator+(const ComplexNumber & Arg1,
            const double & Arg2)
{
    ComplexNumber Res(Arg1);
    return Res +=Arg2;
}

// Binary operators Real + Complex
ComplexNumber operator+(const double & Arg1,
            const ComplexNumber & Arg2)
{
    ComplexNumber Res(Arg1);
    return Res +=Arg2;
}