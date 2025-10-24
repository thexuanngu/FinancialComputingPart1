#include "Practical02/ComplexNumber.hpp"


ComplexNumber::ComplexNumber() : dRe_(0.0), dIm_(0.0) {}

ComplexNumber::ComplexNumber(double dReArg, double dImArg) 
	: dRe_(dReArg), dIm_(dImArg) {}

ComplexNumber & ComplexNumber::operator+=(const ComplexNumber & cnArg)
{
	dRe_ += cnArg.dRe_;
	dIm_ += cnArg.dIm_;
	return *this;
}


std::ostream & ComplexNumber::print(std::ostream & os) const
{
	return os << "(" << dRe_ << ", " << dIm_ << "i)";
}


//non-members
ComplexNumber operator+(const ComplexNumber & Arg1,
			const ComplexNumber & Arg2)
{
	ComplexNumber Res(Arg1);
	return Res +=Arg2;
}


std::ostream & operator<<(std::ostream & os, const ComplexNumber & cnArg)
{
	return cnArg.print(os);
}

