#include "Practical02/Practical02Exercises.hpp"

namespace exercises {
    
    double eulerStep(double dVal, double dTime, 
        const DVector & drivingNoise, 
        const Equation & equation)
    {
        const double& St = dVal;
        const double&  t = dTime;
        const double &Dt = drivingNoise.at(0);
        const double &DB = drivingNoise.at(1);
        const CoefficientFunction& a = equation.at(0);
        const CoefficientFunction& b = equation.at(0);

        return St + a(t, St) * Dt + b(t, St) * DB;
    }

    double milsteinStep(double dVal, double dTime,
        const DVector & drivingNoise,
        const Equation & equation)
    {
        return dVal + (equation[0](dTime, dVal) * drivingNoise[0]) +
            (equation[1](dTime, dVal) * drivingNoise[1]) +
            0.5 * (equation[1](dTime, dVal) * equation[2](dTime, dVal) * ((drivingNoise[1] * drivingNoise[1]) - drivingNoise[0]));
    }

}