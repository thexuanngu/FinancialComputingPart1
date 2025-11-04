#include "Practical02/Practical02Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <cmath>

namespace exercises {

    MCResult MonteCarlo3(double dS0,
        double dT,
        double dR,
        Equation const& equation,
        NumericalStep const& numericalStep,
        unsigned long int iNumberOfSteps,
        unsigned long int iNumberOfPaths,
        PayoffFunction const& payoffFunction)
    {

        // X = future payoff random variable
        double sumXi = 0.0;
        double sumXi2 = 0.0;

        // Simulation Variables
        double S = 0.0;
        double t = 0.0;
        const double delta = dT / iNumberOfSteps;
        const double sqrtDelta = std::sqrt(delta);
        DVector drivingNoise(delta, 0.0);

        // Iterate through each path
        for (unsigned long int i = 0; i < iNumberOfPaths; i++) {
                        // Simulate each stock's final price
                        double & S = dS0; // Reset
                        // Loop through paths
                        for (unsigned long int step = 0; step < iNumberOfSteps; step++) {
                            // Generate Noise
                            drivingNoise.at(1) = utils::NormalDist() * sqrtDelta;

                            // Simulate Stock Price
                            S = numericalStep(S, t, drivingNoise, equation);

                            // Time passes
                            t+= delta;
                        }

                        // Calculate payoff
                        const double Xi = payoffFunction(S);

                        // Caclulate the Data
                        sumXi += Xi;
                        sumXi2 += Xi * Xi;
                    }
            
        // Calculate E[X], E[X^2]
        const double EX = sumXi / iNumberOfPaths;
        const double EX2 = sumXi2 / iNumberOfPaths;

        // Calculate standard deviation of simulated paths
        const double VarX = EX2 - EX * EX;
        const double stdevXhat = std::sqrt(VarX / iNumberOfPaths);

        // Transform it into present value
        const double discount = std::exp(-dR * dT);
        return MCResult{EX * discount, stdevXhat * discount};
    }
}