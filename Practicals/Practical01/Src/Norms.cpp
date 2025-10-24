#include "Practical01/Practical01Exercises.hpp"

namespace exercises {
    double Norm2(const std::vector<double> & dVec) {
        // TODO: Implement this!
        double output = 0.0;
        for (std::vector<double>::size_type i = 0; i < dVec.size(); ++i) {
            // We use std::vector<double>::size_type to ensure type safety in our
            // increment variable, because int is limited, and it ensures it matches
            // the size variable of dVec.size
            output += dVec[i] * dVec[i];
        } 
        output = std::sqrt(output);
        return output;
    }
}

double exercises::NormInf(const std::vector<double> & dVec) {

    // TODO: Implement this!
    return 0.0;
}