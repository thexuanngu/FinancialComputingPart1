#include "Practical01/Practical01Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <random>

#include <vector>
#include <numeric>
#include <cmath>


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
                    // DEBUG: std::cout << "Debug: dSummation = " << dSummation << "i = " << j << std::endl;
                    return exp(-dR * dT) * dSummation / iN;
                   }


    MCResult MonteCarlo2(double dR, 
				   double dSigma, 
				   double dS0, 
				   double dT, 
				   unsigned long int iN, 
				   Payoff call) {
        MCResult output;
        // Fill a single samples vector with payoffs, then compute mean and
        // standard error. The previous code used begin/end from two different
        // temporaries which is undefined behavior and can cause a segfault.
        std::vector<double> samples;
        samples.reserve(iN); // Reserve space to avoid multiple allocations

        // Calculate all the payoffs
        for (int idx = 0; idx < iN; ++idx) {
            double Z = utils::NormalDist();
            double S_T = dS0 * std::exp(dT * (dR - 0.5 * std::pow(dSigma, 2)) + dSigma * std::sqrt(dT) * Z);
            samples.push_back(call(S_T));
        }

        // --- Calculate mean --- //
        double sum = std::accumulate(samples.begin(), samples.end(), 0.0);
        double mean = sum / iN; // (iN > 0) ? sum / static_cast<double>(iN) : 0.0;
        output.mc_estimate = std::exp(-dR * dT) * mean;
        // DEBUG: std::cout << "Debug: mc_estimate = " << output.mc_estimate << std::endl;


        // --- Calculate standard deviation --- //
        double sq_sum = std::accumulate(samples.begin(), samples.end(), 0.0,
            [](double a, double v){ return a + v * v; }); // Lambda function for sum of squares; it starts with 0.0, then looks at the first element
        double mean_sq = sq_sum / iN; // (iN > 0) ? sq_sum / static_cast<double>(iN) : 0.0;
        double variance = mean_sq - mean * mean;
        
        // If there's only one case, no need for braces
        if (variance < 0 && variance > -1e-14) variance = 0; // correct tiny FP negatives

        double std_err = 0.0;
        // If there's only one case, no need for braces; different condition from above
        // if (iN > 0) std_err = std::sqrt(std::max(0.0, variance) / static_cast<double>(iN));  
        std_err = std::sqrt(std::max(0.0, variance) / iN); 
        output.mc_stdev = std::exp(-dR * dT) * std_err;
        // DEBUG: std::cout << "Debug: mc_stdev = " << output.mc_stdev << std::endl;

        return output;
        }

    double callAt1(double dS) {
        return std::max(dS - 1.0, 0.0);
    }
}

// Group of data bundled together -> struct