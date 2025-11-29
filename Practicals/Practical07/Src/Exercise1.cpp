#include "Practical07/Practical07Exercises.hpp"

namespace exercises {
    basket_payoff::basket_payoff(unsigned int indMax = 1)
        : indMax_(indMax) {}
    
    mc::bvector & basket_payoff::operator()(path_out & poArg,
                                            mc::bvector & bvOut) {
        return mc::payoff<mc::bvector>::operator()(poArg, bvOut);
}
}