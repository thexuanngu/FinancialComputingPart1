#include "Practical02/ComplexNumber.hpp"


ComplexNumber::ComplexNumber() : dRe_(0.0), dIm_(0.0) {}

ComplexNumber::ComplexNumber(double dReArg, double dImArg) 
	: dRe_(dReArg), dIm_(dImArg) {}
std::ostream & ComplexNumber::print(std::ostream & os) const
{
	return os << "(" << dRe_ << ", " << dIm_ << "i)";
}
std::ostream & operator<<(std::ostream & os, const ComplexNumber & cnArg)
{
	return cnArg.print(os);
}

// Implementations NOT provided in ComplexNumberSolutions.cpp
// Multiplicative incremental operator (complex)
ComplexNumber & ComplexNumber::operator*=(const ComplexNumber & cnArg)
{
	double r = dRe_ * cnArg.dRe_ - dIm_ * cnArg.dIm_;
	double i = dRe_ * cnArg.dIm_ + dIm_ * cnArg.dRe_;
	dRe_ = r;
	dIm_ = i;
	return *this;
}

// Division incremental operator (complex)
ComplexNumber & ComplexNumber::operator/=(const ComplexNumber & cnArg)
{
	double denom = cnArg.dRe_ * cnArg.dRe_ + cnArg.dIm_ * cnArg.dIm_;
	double r = (dRe_ * cnArg.dRe_ + dIm_ * cnArg.dIm_) / denom;
	double i = (dIm_ * cnArg.dRe_ - dRe_ * cnArg.dIm_) / denom;
	dRe_ = r;
	dIm_ = i;
	return *this;
}

// scalar incremental ops (only those not provided in Solutions)
ComplexNumber & ComplexNumber::operator-=(const double & dArg)
{
	dRe_ -= dArg;
	return *this;
}

ComplexNumber & ComplexNumber::operator*=(const double & dArg)
{
	dRe_ *= dArg;
	dIm_ *= dArg;
	return *this;
}

ComplexNumber & ComplexNumber::operator/=(const double & dArg)
{
	dRe_ /= dArg;
	dIm_ /= dArg;
	return *this;
}

// non-member multiplicative operators
ComplexNumber operator*(const ComplexNumber & Arg1,
			const ComplexNumber & Arg2)
{
	ComplexNumber Res(Arg1);
	return Res *= Arg2;
}

ComplexNumber operator/(const ComplexNumber & Arg1,
			const ComplexNumber & Arg2)
{
	ComplexNumber Res(Arg1);
	return Res /= Arg2;
}

ComplexNumber operator*(const ComplexNumber & Arg1,const double & d)
{
	ComplexNumber Res(Arg1);
	return Res *= d;
}

ComplexNumber operator*(const double & d,const ComplexNumber & Arg2)
{
	ComplexNumber Res(Arg2);
	return Res *= d;
}

ComplexNumber operator/(const ComplexNumber & Arg1,const double & d)
{
	ComplexNumber Res(Arg1);
	return Res /= d;
}

ComplexNumber operator/(const double & d,const ComplexNumber & Arg2)
{
	ComplexNumber Res(d,0.0);
	return Res /= Arg2;
}

ComplexNumber operator-(const ComplexNumber & Arg1,const double & d)
{
	ComplexNumber Res(Arg1);
	return Res -= d;
}

ComplexNumber operator-(const double & d,const ComplexNumber & Arg2)
{
	ComplexNumber Res(d,0.0);
	return Res -= Arg2;
}

