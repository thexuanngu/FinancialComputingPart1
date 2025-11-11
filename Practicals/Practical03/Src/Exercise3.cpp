#include "Practical03/Practical03Exercises.hpp"

namespace exercises {
    // Our function definitions go inside the exercises namespace...
    int lastElement(const LinkedList03 & l) {
        // Const => we are not modifying the list => pointer to a const
        const LinkedList03 * current = &l;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        return current->getData();
    }

    int lastElementRecursive(const LinkedList03 & l) {
        if (!l.hasNext()) {
            return l.getData();
        }
        return lastElementRecursive(*l.getNext());
    }
}