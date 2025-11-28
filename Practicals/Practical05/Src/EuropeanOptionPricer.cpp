#include "Practical05/Practical05Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"

namespace exercises {
    EuropeanOptionPricer::EuropeanOptionPricer(const std::vector<BVector> & factorsAt0,
             const BVector & valuesAtT,
             const FVector & testFunctions) : 
             m_TestFunctions(testFunctions),
             m_Coefficients(Regression(valuesAtT, factorsAt0, testFunctions)) {}


    double EuropeanOptionPricer::operator()(const BVector & factorAt0) {
    // Todo: implement operator()
    return Projection(factorAt0, m_TestFunctions, m_Coefficients);
}

    BVector MonteCarlo4(std::vector<BVector> vS0,
                double dR,
                double dSigma1,
                double dSigma2,
                double dRho,
                double dT,
                Function const& payoff) {
                    // We return the (discounted!) expected payoff for each pair of initial condition
                    BVector result(vS0.size());

                    // Constants
                    const double sqrtT = std::sqrt(dT);
                    const double drift1 = (dR + 0.5 * dSigma1 * dSigma1) * dT;
                    const double drift2 = (dR + 0.5 * dSigma2 * dSigma2) * dT;
                    const double dRho2 = std::sqrt(1.0 - dRho * dRho);
                    const double discount = std::exp(-dR * dT);

                    for (int idx = 0; idx < vS0.size(); idx++) {
                        // Generate some noise
                        const double B1 = utils::NormalDist() * sqrtT;
                        const double B2 = utils::NormalDist() * sqrtT;

                        // Simulate stock value
                        BVector St(2);
                        St[0] = vS0.at(idx)[0] * std::exp(drift1 + dSigma1 * B1);
                        St[1] = vS0.at(idx)[1] * std::exp(drift2 + dSigma2 * (dRho * B1 + dRho2 * B2));

                        result[idx] = payoff(St) * discount; // Discounted payoff
                    }

                    return result;
                }
}