#include "Practical05/Practical05Exercises.hpp"
#include <boost/numeric/ublas/lu.hpp>

namespace exercises {
    BVector Regression(const BVector & yVals, 
		   const std::vector<BVector> & factors, 
		   const FVector & testFunctions) {
            // We want to solve PhiT Phi beta = PhiT Y
            // This is solving A x = b
            // where A = PhiT Phi
            //       b = PhiT Y

            // Construct Phi matrix
            BMatrix PhiT(testFunctions.size(), factors.size()); // The rows are the functions
            for (int row = 0; row < testFunctions.size(); row++) {
                for (int col = 0; col < factors.size(); col++) {
                    PhiT(row, col) = testFunctions[row](factors[col]); // It is a function
                } // Can't be const & because we keep updating it
            }

            // Compute A = PhiT * Phi -> We can't use const because of LU decomp
            BMatrix A = prod(PhiT, trans(PhiT));

            // Compute b = PhiT * Y
            BVector b = prod(PhiT, yVals);


            // Look at Lecture 9 for LU! -> This is basically doing the calculation for the regression coefficients
            boost::numeric::ublas::lu_factorize(A);
            boost::numeric::ublas::lu_substitute<const BMatrix, BVector>(A, b);

            return b;

           }
        
    double Projection(const BVector & factor, 
		  const FVector & testFunctions, 
		  const BVector & coefficients) {
            // To Do
            // Just an inner product, can be done in one line, but a loop is always good enough
            double result = 0.0;
            for (int idx = 0; idx < testFunctions.size(); idx++) {
                result += coefficients[idx] * testFunctions[idx](factor);
            }
            return result;
          }
}