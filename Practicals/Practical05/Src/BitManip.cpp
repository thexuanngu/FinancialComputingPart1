#include "Practical05/Practical05Exercises.hpp"

namespace exercises {
    unsigned int subtract(unsigned int a, unsigned int b) {
        // Bitwise subtraction: compute a - b using only bitwise ops
        // Algorithm: while there is a borrow, compute xor (partial difference)
        // and the borrow bits, then shift borrow left and iterate.
        while (b != 0) {
            unsigned int borrow = (~a) & b;      // bits that need borrowing
            unsigned int xor_diff = a ^ b;       // partial difference without borrows
            a = xor_diff;
            b = borrow << 1;                     // propagate borrow to next bit
        }
        return a;
    }

    void swap(unsigned int & a, unsigned int & b) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}