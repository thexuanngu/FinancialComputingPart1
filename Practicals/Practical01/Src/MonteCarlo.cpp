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
                    int j = 0;
                    for(int i = 0; i < iN; i++) {
                        dSummation += sumTerms(dR, dS0, dSigma, dT, dK);
                        j++;
                    }
                    std::cout << "Debug: dSummation = " << dSummation << "i = " << j << std::endl;
                    return exp(-dR * dT) * dSummation / iN;
                   }


    MCResult MonteCarlo2(double dR, 
				   double dSigma, 
				   double dS0, 
				   double dT, 
				   unsigned long int iN, 
				   Payoff call) {
        MCResult ouput;

        ouput.mc_estimate = exp (-dR *dT) * std::accumulate(
            std::vector<double>(iN).begin(),
            std::vector<double>(iN).end(),
            0.0,
            [&](double current_sum, double element) {
                double S_T = dS0 * exp(dT * (dR - 0.5 * pow(dSigma, 2)) + dSigma * sqrt(dT) * utils::NormalDist());
                return current_sum + call(S_T);
            }
        ) / iN;
        std::cout << "Debug: mc_estimate = " << ouput.mc_estimate << std::endl;

        ouput.mc_stdev = exp (-dR *dT) * sqrt((std::accumulate(
            std::vector<double>(iN).begin(),
            std::vector<double>(iN).end(),
            0.0,
            [&](double current_sum, double element) {
                double S_T = dS0 * exp(dT * (dR - 0.5 * pow(dSigma, 2)) + dSigma * sqrt(dT) * utils::NormalDist());
                return current_sum + call(S_T);
            }
        ) / iN) - pow(ouput.mc_estimate, 2)) / sqrt(iN);
        std::cout << "Debug: mc_stdev = " << ouput.mc_stdev << std::endl;

        return ouput;
        }

    double callAt1(double dS) {
        return 42.0;
    }
}

// Group of data bundled together