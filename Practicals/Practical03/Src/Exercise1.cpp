#include "Practical03/Practical03Exercises.hpp"

namespace exercises {
    // Define the functions declared in Practical03Exercises.hpp here
    unsigned int length(const LinkedList03 & l) {
        // Get the length of the LinkedList03 l
        int counter = 0;
        const LinkedList03 * current = &l;
        while (current != nullptr) {
            counter++;
            current = current->getNext();
        }
        return counter;
    }

    unsigned int lengthRecursive(const LinkedList03 & l) {
        // Get the length of the LinkedList03 l using recursion
        if (!l.hasNext()) {
            return 1;
        } else {
            return 1 + lengthRecursive(*l.getNext()); // Dereference pointer
        }
    }
}