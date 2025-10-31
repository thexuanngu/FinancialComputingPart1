#include "Practical02/Practical02Exercises.hpp"

namespace exercises {
    
    double eulerStep(double dVal, double dTime, 
        const DVector & drivingNoise, 
        const Equation & equation)
    {
        return dVal + (drivingNoise[0] * equation[0](dTime, dVal)) + 
        (drivingNoise[1] * equation[0](dTime, dVal));
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