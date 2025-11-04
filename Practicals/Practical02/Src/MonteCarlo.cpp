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
        const double delta = dT / iNumberOfSteps;
        DVector drivingNoise = {delta, 0.0};
        const double sqrtDelta = sqrt(delta);

        for (unsigned long int i = 0; i < iNumberOfPaths; ++i) {
            // 1. Simulate S (now it's a bit more complex).
            // S starts at S0, time t starts at 0
            double S = dS0;
            double t = 0.0;

            for (unsigned long step = 0; step < iNumberOfSteps; ++step) {
                // Noise
                drivingNoise.at(1) = utils::NormalDist() * sqrtDelta;

                // Stock evolves
                S = numericalStep(S, t, drivingNoise, equation);

                // Advance time
                t += delta;
            }

            // 2. Calculate payoff Xi
            const double Xi = payoffFunction(S);
            sumXi += Xi;
            sumXi2 += Xi * Xi;
        }

        // 3. Estimate E[X], E[X^2]
        const double EX = sumXi / iNumberOfPaths;
        const double EX2 = sumXi2 / iNumberOfPaths;

        // 4. Calculate Standard deviation of estimate
        const double stdDev = sqrt( (EX2 - EX*EX) /iNumberOfPaths);

        // 5. Transform future value to present value
        const double discount = exp(-dR * dT);
        return MCResult{EX * discount, stdDev * discount};
    }
}