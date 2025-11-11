#include "Practical04/BinaryOperators.hpp"
#include <cmath>

// Continuously compounding yield corresponding to discount factor
double exercises::DF2Yield::operator()(const double dDiscountFactor, const double dTimeToMaturity) const {
    // Todo implement!
    double logTerm = std::log(dDiscountFactor) / (-dTimeToMaturity);
    return logTerm;
}

double exercises::Yield2DF::operator()(const double dYield, const double dTimeToMaturity) const{
    // Todo implement!
    double expTerm = -dYield * dTimeToMaturity;
    return std::exp(expTerm);
}

double exercises::DF2Libor::operator()(const double dDiscountFactor, const double dTimeToMaturity) const {
    // Todo implement!
    double liborRate = ((1.0 / dDiscountFactor) - 1.0) / dTimeToMaturity;
    return liborRate;
}

double exercises::Libor2DF::operator()(const double dLibor, const double dTimeToMaturity) const {
    // Todo implement!
    double discountFactor = 1.0 / (1.0 + dLibor * dTimeToMaturity);
    return discountFactor;
}