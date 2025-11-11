#include "Practical03/Practical03Exercises.hpp"

namespace exercises {
    // Our function definitions go inside the exercises namespace...
    int nextToLast(const LinkedList03 & l) {
        const LinkedList03 * current = &l;
        while (current->getNext()->getNext() != nullptr) {
            current = current->getNext();
        }
        return current->getData();
    }

    int nextToLastRecursive(const LinkedList03 & l) {
        if (!(l.getNext()->hasNext())) {
            return l.getData();
        }
        return nextToLastRecursive(*l.getNext());
    }

    LinkedList03 clone(const LinkedList03 & l) {
        LinkedList03 cloned_l(l.getData());
        const LinkedList03 * current = l.getNext();
        while (current != nullptr) {
            cloned_l.append(current->getData());
            current = current->getNext();
        }
        return cloned_l;
    }
}