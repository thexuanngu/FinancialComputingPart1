#include "Practical01/Practical01Exercises.hpp"

namespace exercises {
    double MonteCarlo1(double dR, 
				   double dSigma, 
				   double dS0, 
				   double dK , 
				   double dT, 
				   unsigned long int iN) {
                    return 0.0;
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