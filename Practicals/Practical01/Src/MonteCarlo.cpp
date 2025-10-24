#include "Practical01/Practical01Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <random>



namespace exercises {

    double sumTerms(const double &dR,
                const double &dS0,
                const double &dSigma,
                const double &dT,
                const double &dK) {
                                    double Z_i = utils::NormalDist();
                                    double expression = dS0 * exp(dT*(dR - 0.5*pow(dSigma, 2)) + dSigma * sqrt(dT) * Z_i) - dK;
                                    return std::max(expression, 0.0);
                                    }
    double MonteCarlo1(double dR, 
				   double dSigma, 
				   double dS0, 
				   double dK , 
				   double dT, 
				   unsigned long int iN) {

                    // TODO: Implement this!
                    double dSummation(0.0);

                    for(int i; i < iN; i++) {
                        dSummation += sumTerms(dR, dS0, dSigma, dT, dK);
                    }

                    return exp(-dR * dT) * dSummation / iN;
                   }


    MCResult MonteCarlo2(double dR, 
				   double dSigma, 
				   double dS0, 
				   double dT, 
				   unsigned long int iN, 
				   Payoff call) {
        MCResult ouput;
        ouput.mc_estimate = 0.0;
        ouput.mc_stdev = 0.0;
        return ouput;
                   }

    double callAt1(double dS) {
        return 42.0;
    }
}

// Group of data bundled together