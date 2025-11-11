#include "Practical03/Practical03Exercises.hpp"

namespace exercises {
    // Our function definitions go inside the exercises namespace...
    bool hasElement(const LinkedList03 & l, int i) { 
        // Get the length of the LinkedList03 l
        const LinkedList03 * current = &l;
        while (current != nullptr) {
            if (current->getData() == i) {
                return true;
            }
            
            current = current->getNext();
            
        }
        return false;
    }

    bool hasElementRecursive(const LinkedList03 & l, int i) {
        // Get the length of the LinkedList03 l using recursion
        if (l.getData() == i) {
            return true;
        } else if (!l.hasNext()) {
            return false;
        }
        else {
            return hasElementRecursive(*l.getNext(), i);
        }
    }
}
