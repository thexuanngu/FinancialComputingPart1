# Setting up Practical 03

This is a markdown file, you can open it in Visual Studio Code to se it formatted nicely
and use its links. 

For the links to work correctly, you'll need to place this file inside
the **CppCourse** > **Practicals** > **Practical03** folder you get in step 1. 
You can place it elsewhere inside **CppCourse** in the meantime.

Steps (1) and (2) should be familiar by now, and in (3) and (4)
we look at how to set up the dummy solutions.
You should be able to have a go at the practical with just these,
but I've added a few additional notes in (5), (6) and (7)
that could be useful.

<!-- TOC -->
* [Setting up Practical 03](#setting-up-practical-03)
  * [1) The Practical 03 folder](#1-the-practical-03-folder)
  * [2) Enabling Practical03 in the global CMake file.](#2-enabling-practical03-in-the-global-cmake-file)
  * [3) Setting up our `.cpp` file(s)](#3-setting-up-our-cpp-files)
  * [4) Dummy implementations](#4-dummy-implementations)
  * [5) What's `LinkedList03`?](#5-whats-linkedlist03)
    * [Internal Data](#internal-data)
    * [What you can do with it](#what-you-can-do-with-it)
    * [Be careful with copy constructor and copy assignment](#be-careful-with-copy-constructor-and-copy-assignment)
  * [6) Recursion](#6-recursion)
    * [Examples of recursive functions in LinkedLists.cpp](#examples-of-recursive-functions-in-linkedlistscpp)
    * [What are Stack Overflows?](#what-are-stack-overflows)
  * [7) Cloning](#7-cloning)
<!-- TOC -->

## 1) The Practical 03 folder

Go to the [course site](https://courses.maths.ox.ac.uk/course/view.php?id=5974),
and click on **Practical exercises** to download the 
**Practicals.zip** file.
Extract this and inside you'll find **Practical03.zip**
along with the other practicals.
Extract **Practical03.zip** and you'll get a **Practical03** folder.

Place the **Practical03** inside **CppCourse** > **Practicals**.

The folder structure of **CppCourse** should end up looking like this.

```
CppCourse
├─ boostRoot
├─ ...
├─ Practicals
│  ├─ Practical01
│  ├─ Practical02
│  └─ Practical03
│     ├─ Src 
│     ├─ CMakeLists.txt
│     ├─ ...
│     └─ Practical03Exercises.hpp 
└─ CMakeLists.txt
```

As an optional step, place this file inside the **Practical03** folder,
which would then look like this

```
Practical03
├─ Src
│  ├─ LinkedLists.cpp
│  └─ Practical03.cpp
├─ CMakeLists.txt
├─ CppProblemSheet3.pdf
├─ LinkedLists.hpp
├─ Practical03_output.txt
├─ Practical03Exercises.hpp
└─ setting_up_practical03.md
```

If you do, you should be able to click on 
[this link to open CppProblemSheet3.pdf](./CppProblemSheet03.pdf)


## 2) Enabling Practical03 in the global CMake file.

Go to the
[global CMakeLists.txt file](../../CMakeLists.txt),
and enable Practical03 by uncommenting the appropriate line,
from:

```cmake
# Practicals and solutions
add_subdirectory(Practicals/Practical01)
#add_subdirectory(Practicals/Practical01Solutions)
add_subdirectory(Practicals/Practical02)
#add_subdirectory(Practicals/Practical02Solutions)
#add_subdirectory(Practicals/Practical03)
#add_subdirectory(Practicals/Practical03Solutions)
```

To

```cmake
# Practicals and solutions
add_subdirectory(Practicals/Practical01)
#add_subdirectory(Practicals/Practical01Solutions)
add_subdirectory(Practicals/Practical02)
#add_subdirectory(Practicals/Practical02Solutions)
add_subdirectory(Practicals/Practical03)
#add_subdirectory(Practicals/Practical03Solutions)
```

Once you do, you should be able to select the `Practical03` project
in the CMake Plugin tab, 
and try to build and run it (which at this point should
have errors).

## 3) Setting up our `.cpp` file(s)

If you run `Practical03` you should get errors telling you that
some functions are undefined (the particular error will change
depending on your compiler). The functions that need definition
are
- `exercises::length`
- `exercises::lengthRecursive`
- `exercises::hasElement`
- `exercises::hasElementRecursive`
- `exercises::lastElement`
- `exercises::lastElementRecursive`
- `exercises::nextToLast`
- `exercises::nextToLastRecursive`
- `exercises::clone`

These functions are declared, but not defined, in
[Practical03Exercises.hpp](./Practical03Exercises.hpp).

We create a new `.cpp` file inside of Src where we'll add
the implementations of these functions.
You can have multiple `.cpp` files instead, for example
one for each exercise, if you prefer.

Inside our `.cpp` file we'll need to include
the declarations of the functions in 
[Practical03Exercises.hpp](./Practical03Exercises.hpp),
so we add;
```c++
#include "Practical03/Practical03Exercises.hpp"
```

Next, since all the function declarations in
[Practical03Exercises.hpp](./Practical03Exercises.hpp)
are inside the `exercises` namespace,
we also make sure to define the function in our `.cpp` file
inside the `exercises` namespace;
```c++
#include "Practical03/Practical03Exercises.hpp"
namespace exercises {
    // Our function definitions go inside the exercises namespace...
    unsigned int length(const LinkedList03 & l) { /* ... */}
}
```
This could alternatively be done by defining each function
as `exercises::functionName`

```c++
#include "Practical03/Practical03Exercises.hpp"
// Or our function definitions need the "exercises::" prefix.
unsigned int exercises::length(const LinkedList03 & l) { /* ... */}
```

## 4) Dummy implementations

Let's have a look at one of the function declarations inside
[Practical03Exercises.hpp](./Practical03Exercises.hpp),
the one for `exercises::length`.

```c++
/** Computes the length of a linked list.
 * @param l linked list
 * @return length of l
 */
unsigned int length(const LinkedList03 & l);
```

It takes a `LinkedList03` and returns an `unsigned int`.
`LinkedList03` is defined in 
[LinkedLists.hpp](./LinkedLists.hpp),
which is included inside
[Practical03Exercises.hpp](./Practical03Exercises.hpp)
in the line
```c++
#include "LinkedLists.hpp"
```
So by including
[Practical03Exercises.hpp](./Practical03Exercises.hpp)
we're already including
[LinkedLists.hpp](./LinkedLists.hpp).
There's nothing else we need to do to our `.cpp` file
to be able to use `LinkedList03`.

Now let's implement a dummy solution!

We copy the declaration and place it inside our C++ file,
then since `exercises::length` returns an `unsigned int`
it's ok if we just return `0` for now;
```c++
// Inside our C++ file.
#include "Practical03/Practical03Exercises.hpp"
namespace exercises {

    /** Computes the length of a linked list.
    * @param l linked list
    * @return length of l
    */
    unsigned int length(const LinkedList03 & l) {
        return 0;
    }
    
    // Other definitions will go here...
}
```

You can do the same for the rest of the functions, 
though some functions have different *return types*,
here's some dummy values we can use;

If the function returns an `int` or an `unsigned int`,
like `length`, `lastElement`, `nextToLast` and their
recursive variants,
the dummy implementations of our functions can simply
```c++
return 0;
```

If the function returns a `bool`,
like `hasElement` or `hasElementRecursive`,
then we can instead
```c++
return false;
```

Finally, if the function returns a `LinkedList03`... 
We'll have to construct a `LinkedList03`,
which we can do by using its constructor, 
which will be discussed in the next section.
```c++
return LinkedList03(0);
```

Once you do so, you should be able to run `Practical03`
without any compiler errors!

If you have any compiler errors at this point,
let me know and I'll see if I can help.


## 5) What's `LinkedList03`?

This is the third implementation of a linked list as in the `Lecture06`,
and was explained in lectures.
The [header file LinkedLists.hpp](./LinkedLists.hpp)
and [definition of its functions LinkedLists.cpp](./Src/LinkedLists.cpp)
are also inside `Practical03`.

### Internal Data
```c++
class LinkedList03
{
    // ...
private:
    int mData;
    LinkedList03 * mNext;
    unsigned int mRefCount;
};
```

In this file I'll call the first element of a Linked List
its **head**, and the rest of the elements its **tail**.

So internally `LinkedList03` only stores the data of its **head**
in `mData`,
and points towards another `LinkedList03` containing its **tail**
in `mNext`.

It also keeps track of how many other `LinkedList03` link into it
in `mRefCount`.

### What you can do with it

Here's part of the header in 
[LinkedLists.hpp](./LinkedLists.hpp), 
with some added comments,
```c++
class LinkedList03
{
public:
    // Constructor
    LinkedList03(int);
    
    // Copy constructor
    LinkedList03(const LinkedList03 &);
    
    // Destructor
    ~LinkedList03();	
    
    // Copy assignment
    LinkedList03 & operator=(const LinkedList03 &);
    
    // Used to construct multiple elements of the list
    void append(int);
    
    // Used to access tail
    LinkedList03 * getNext() const;
    bool hasNext() const;
    
    // Manipulate head data
    int getData() const;
    void setData(int);
    
    // Print!
    std::ostream & print(std::ostream &) const;
    
    //...
}
```

There are no "empty" `LinkedList03`, 
each of them has to be initialized with its head.

You can construct a linked list whose head is `0` with
```c++
LinkedList03 myList(0);
```

The copy-constructor creates a linked list with a new head,
but *shares the same tail as the previous list*.
The copy-assignment similarly has the two linked lists
involved have a different head with the same value,
but share the exact same tail.

Be careful when using these.

```c++
// Copy constructor
LinkedList03 listB(listA);

// This changes listB's head, leaving listA unaffected
listB.setData(42);

// This changes listB's tail's data, also changing listA's tail's data.
listB.getNext()->getNext()->setData(99);
```



The main way you'll build a LinkedList is by using `append`.
It works like `std::vector<int>::push_back`.

You can also print out a list with `std::cout << myList;`,
this can be very useful for debugging.

```c++
LinkedList03 listA(1);
for (int i = 2; i < 10; i++) {
    listA.append(i * i);
}
cout << "List A: " << listA << '\n';
// List A: 1, 4, 9, 16, 25, 36, 49, 64, 81 -end-of-list.
```

You can change the head's data with `getData` and `setData`.
You can access the tail through the pointers returned by
`getNext`. Remember that if you have a pointer to an
element, and one to access a member of an element,
you can use `pointer->member` instead of `(*pointer).member`.

```c++
// Change the data of the head
listA.setData(42); 

// Get the data of the 2nd element.
listA.getNext()->getData(); 

// Change the data of the 3rd element.
listA.getNext()->getNext()->setData(-1);
```

Make sure to use `hasNext` to check if a `LinkedList03`
has a tail! Otherwise, you're going to start running into errors.

### Be careful with copy constructor and copy assignment

What does this code do?
```c++
// Copy assignment?
LinkedList03 listD(0); listD.append(1); listD.append(0);
*(listD.getNext()->getNext()) = listD;
```
If I try to print listD...
```
List D: 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 
[it continues to print 0 and 1 for like a long time]
Process finished with exit code 139 (interrupted by signal 11:SIGSEGV)
```

This is an example of a *stack overflow*, more details on this later.

## 6) Recursion

A recursive function is a function that calls itself.
A classic example is the factorial of a number

$$n! = n \cdot [(n-1)!] = \prod_{k=1}^n k$$

Let's implement it with a loop and without recursion;
```c++
int factorial(int n) {
    int result = 1;
    for (int k = 1; k <= n; k++) {
        result *= k;
    }
    return result;
}
```
As you can see, we can implement `factorial` by using loops,
without any recursion (as the function does not call itself).

However, it's also possible to implement functions recursively!
```c++
int factorialRecursive(int n) {
    if (n <= 1) { return 1; }
    else { return n * factorialRecursive(n-1); }
}
```

Just like in proofs by induction, 
it's vital to have a "base case" like
`if (n <= 1) { return 1; }`,
as otherwise the function could run "forever"...
or until it reaches a "stack overflow".

Some compilers can do "tail call optimization"
if the return value is a function call,
this makes it so that recursive functions don't increase the
call stack at all! 
(Setting up your compiler to do tail call optimization
is a bit tricky, and will depend on your specific compiler).

Here's another implementation of the factorial function,
which replaces `return n * f(...);` with `return f(...);`
to help the compiler use tail call optimization.

```c++
int factorialRecursive2(int n, int acc = 1) {
    if (n <= 1) { return acc; }
    else { return factorialRecursive2(n-1, acc * n); }
}
```

### Examples of recursive functions in LinkedLists.cpp

Let's have a look at 
[LinkedLists.cpp](./Src/LinkedLists.cpp).

The `append` function calls itself,
so it's a recursive function.
```c++
void LinkedList03::append(int arg) {
    if(hasNext())
        mNext->append(arg); // note: recursive fn call
    else 
        acquireNext(new LinkedList03(arg));
}
```

The `LinkedList03::print` function also uses recursion, 
since it calls itself. 
```c++
std::ostream & LinkedList03::print(std::ostream & os) const {
    os << mData ;

    if (hasNext()){
        os << ", " ;
        mNext->print(os);    
    }
    else
        os << " -end-of-list.";

    return os;
}
```

We could add tail call optimization if we return a function call
when we use recursion.
```c++
std::ostream & LinkedList03::print(std::ostream & os) const {
    os << mData ;

    if (hasNext()){
        os << ", " ;
        return mNext->print(os);    
    }
    else
        os << " -end-of-list.";

    return os;
}
```
Now if I try to print `listD`, it also runs into a stack overflow.
However, once I managed to set up the right compiler optimizations,
I was able to print `listD` forever, without ever running into
a stack overflow.

Uhh... this is still a problem. You usually want functions to
eventually terminate.


### What are Stack Overflows?

When you call a function, the computer goes execute some code,
but later *returns* the where you were before, 
this is also why the return statement is called "return".

Now the question is how does the computer know where to return to?

Well, it keeps a "stack" of the locations where it needs to return.
Every time you call a function, the computer writes down the current
location and puts it on top of the stack. When a function returns,
it looks at what's on top of the stack and returns there.

It's a stack because maybe you call `functionA`, which
calls `functionB`, which itself calls `functionC`.
When `functionC` returns, it needs to return to the right
place inside `functionB`, and during all this time,
we still need to remember where `functionA` is supposed to return,
lest we forget.

This stack has some memory allocated. If we call 
functions within functions within functions..., 
we will eventually run out of this memory,
which is a *stack overflow*. While it's possible to get there
with non-recursive functions,
recursive functions can very easily run into stack overflows if
we're not careful and the function calls itself too much.

What call tail optimization does is,
if we return and call a function at the same time,
it doesn't increase the stack, instead it just moves onto the
next function.
It's essentially saying "we don't need to remember where we are,
because we're about to return to the previous location anyway,
we just need to remember where that is, 
and that's already in the stack".

This helps keep the stack smaller if functions have this
tail call optimization. It doesn't stop us from evaluating
infinitely recursive functions, though, which can be dangerous.



## 7) Cloning

At the moment, the copy constructor and the copy assignment
don't create a new "collection of things that has the same values
as the previous list". 
The head is now different, (though it has the same value),
but the tail is exactly the same, not in value, but it's the same object!

```c++
// Create a list
LinkedList03 listA(1);
for (int i = 2; i < 10; i++) {
    listA.append(i * i);
}
cout << '\t' << "List A: " << listA << '\n';
// List A: 1, 4, 9, 16, 25, 36, 49, 64, 81 -end-of-list.


// Copy constructor
LinkedList03 listB(listA);

// This changes listB's head, leaving listA unaffected
listB.setData(42);

// This changes listB's tail data, also changing listA's data.
listB.getNext()->getNext()->setData(99);

cout << '\t' << "List A: " << listA << '\n';
// List A: 1, 4, 99, 16, 25, 36, 49, 64, 81 -end-of-list.

cout << '\t' << "List B: " << listB << '\n';
// List B: 42, 4, 99, 16, 25, 36, 49, 64, 81 -end-of-list.
```

The `exercises::clone` should give us a new `LinkedList03`
which does not share the same tail as the previous list,
but instead has its own separate tail, which
has the same values as the previous list.


