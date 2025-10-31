#include "Practical01/Practical01Exercises.hpp"
#include <numeric>
#include <cmath>

namespace exercises {
    double Norm2(const std::vector<double> & dVec) {
        // TODO: Implement this!
        double output = 0.0;
        for (std::vector<double>::size_type i = 0; i < dVec.size(); ++i) {
            // We use std::vector<double>::size_type to ensure type safety in our
            // increment variable, because int is limited, and it ensures it matches
            // the size variable of dVec.size
            output += dVec[i] * dVec[i];

            // Esteban's code
            /*
            double sumSquares = 0.0;
            for (int idx = 0, idx < dVec.size(); idx++) {
                sumSquares += dVec.at(idx) * dVec.at(idx);
                --> .at() will do bounds checking!
            }

            return std::sqrt(sumSquares);
            */
        } 
        output = std::sqrt(output);
        return output;
    }
}

double exercises::NormInf(const std::vector<double> & dVec) {

    // TODO: Implement this!
    return std::accumulate(dVec.begin(), dVec.end(), 0.0, 
                            [](double current_max, double element){
                                return std::max(current_max, std::abs(element));
                            });
    // The [](...){...} is the C++ equivalent of a lambda function!
    // For accumulate, the lambda function MUST take 2 arguments (normally, it just adds)
    // Arguments of the function would be ((currently stored value), (next value in iteration))
    // std::accumulate (in numeric) is able to 'cache' the value
    // The function has to be a 'binary' operation

    // Esteban's code
            /*
            double maxAbs = 0.0;
            for (const double& value : dVec) {
                maxAbs = std::max(maxAbs, std::abs(value));
                maxAbs = maxAbs < std::abs(value) ? std::abs(value) : maxAbs;
            }
            return maxAbs;
            */                        

}