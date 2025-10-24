# Setting up Practical02

This is a markdown file, you can view the file 
in a more visual way in Visual Studio Code with 
**View > Command Palette > Markdown: Open Preview**.

Place this file inside the **Practical02** folder,
which should be placed inside the 
**CppCourse/Practicals** folder.

```
CppCourse
├─ boostRoot
├─ ...
├─ Practicals
│  ├─ Practical01
│  └─ Practical02
│     ├─ Src 
│     │  ├─ ComplexNumber.cpp
│     │  └─ Practical02.cpp
│     ├─ CMakeLists.txt
│     ├─ ComplexNumber.hpp
│     ├─ CppProblemSeet02.pdf
│     ├─ Practical02Exercises.hpp
│     └─ setting_up_practical02.md 
└─ CMakeLists.txt
```


# Adding Practical02 to the project

To be able to configure the Practical02, build it and run it, 
we'll need to let the 
[global CMakeLists.txt](../../CMakeLists.txt) 
file know  that we've added Practical02.

Open the 
[global CMakeLists.txt](../../CMakeLists.txt) 
and go to where there is the `# Practicals and Solutions`

```cmake
# Practicals and solutions
add_subdirectory(Practicals/Practical01)
#add_subdirectory(Practicals/Practical01Solutions)
#add_subdirectory(Practicals/Practical02)
#add_subdirectory(Practicals/Practical02Solutions)
#add_subdirectory(Practicals/Practical03)
# ...
```

Uncomment the line containing Practical02,
by removing the `#`.

```cmake
# Practicals and solutions
add_subdirectory(Practicals/Practical01)
#add_subdirectory(Practicals/Practical01Solutions)
add_subdirectory(Practicals/Practical02)
#add_subdirectory(Practicals/Practical02Solutions)
#add_subdirectory(Practicals/Practical03)
# ...
```

Saving the changes to the 
[global CMakeLists.txt](../../CMakeLists.txt)
should automatically run **CMake: Configure**
for us, but it's always a good idea to 
**View > Command Palette > CMake: Configure**
again for good measure.

If all went alright, you should now be able to see
the **Practical02** target in the
**CMake plugin's tab / Project Outline subtab**.


# First build

As always, we need to 
**Configure > Build > Run in Terminal**.

Right click on the **Practical02** target 
(in the
**CMake plugin's tab / Project Outline subtab**),
then select **Set Build Target**.
We only need to do so once, when changing build targets.

Next, right click again on the **Practical02**
target, and select **Build**. (There is also a button to the
right of the **Practical02** target that does so).

At this point, we expect to run into errors in the terminal,
There should be several tabs; Problems, Output, Terminal, Ports,
Debug console, and to the right of these tabs there should be
a textbox for filtering errors.
In this filtering textbox, write "undefined", 
to narrow down the list of undefined functions.

There will be a long list of errors, one of them might look like;
```
[build] /path/to/CppCourse/Practicals/Practical02/Src/Practical02.cpp:85:(.text+0x661): undefined reference to `exercises::eulerStep(double, double, std::vector<double, std::allocator<double> > const&, std::vector<std::function<double (double, double)>, std::allocator<std::function<double (double, double)> > > const&)'
```

In each of these errors, you should focus on the "undefined reference to ???";

```
[path]: undefined reference to `exercises::eulerStep(...)'
```

As mentioned during class, these are *linking errors*,
caused by trying to use functions that have been
declared, but not yet defined.

Our first task is to define dummy implementations
for all declared functions,
and the next task is to replace the dummy implementations
with actual implementations.

# Dummy implementations

Have a look at the [CMakeLists.txt file inside Practical02](./CMakeLists.txt).

```cmake
file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical02 ${sourcefiles} ${headerfiles})

target_link_libraries(Practical02 Utils)
```

This means the project is built from the header files 
ending in `.hpp` inside of 
**CppCourse/Practicals/Practical02**,
and the C++ files ending in `.cpp` inside of
**CppCourse/Practicals/Practical02/Src**.

To implement our functions, we'll need to create
new `.cpp` files inside of
**CppCourse/Practicals/Practical02/Src**.
However, CMake does not notice these new files
until we run **CMake: Configure** again, 
so the editor will complain that they can't 
include things until we run  **CMake: Configure** again.

> Be sure to run  **CMake: Configure** again
> every time you add a new C++ file!


## Exercises 1 & 2

For exercises 1 and 2 we'll need to define the functions
`exercises::eulerStep` and `exercises::milsteinStep`,
which are declared in [Practical02Exercises.hpp](./Practical02Exercises.hpp).

```c++
/* Includes ... */ 

namespace exercises
{
    /* Typedefs... */

    /** EulerStep - corresponding to the scalar SDE
    *               dS(t)=a(t,S(t))dt+b(t,S(t))dB(t)
    * @param dVal initial stockprice
    * @param dTime time 
    * @param drivingNoise contains (Dt,DB)
    * @param equation contains the coefficient functions (a,b)
    * @return result of Euler step
    */
    double eulerStep(double dVal, 
        double dTime, 
        const DVector & drivingNoise, 
        const Equation & euqation);

    /** milsteinStep - corresponding to the scalar SDE
    *                  dS(t)=a(t,S(t))dt+b(t,S(t))dB(t)
    * @param dVal initial stockprice
    * @param dTime time
    * @param drivingNoise contains (Dt,DB)
    * @param equation contains the coefficient functions (a,b,b')
    * @return result of Milstein step
    */
    double milsteinStep(double dVal, 
        double dTime,
        const DVector & drivingNoise,
        const Equation & euqation);

    /* MonteCarlo3 ... */
}
```

As these are functions that return `double`,
we can write a dummy implementation by returning `0.0`.

We first create a C++ file, which I'll call
**StepFunctions.cpp**, inside of
**CppCourse/Practicals/Practical02/Src**.

We need to include the header file, 
so we copy the include from 
[Practical02.cpp](Src/Practical02.cpp).
```c++
#include "Practical02/Practical02Exercises.hpp"
```

All these functions are inside of the `exercises` namespace,
so we add their definitions within this namespace;

```c++
#include "Practical02/Practical02Exercises.hpp"

namespace exercises {
    
    double eulerStep(double dVal, double dTime, 
        const DVector & drivingNoise, 
        const Equation & euqation)
    {
        return 0.0;
    }

    double milsteinStep(double dVal, double dTime,
        const DVector & drivingNoise,
        const Equation & euqation)
    {
        return 0.0;
    }

}
```

Alternatively, we could have defined `exercises::eulerStep`
directly.

```c++
#include "Practical02/Practical02Exercises.hpp"
    
double exercises::eulerStep(double dVal, double dTime, 
    const DVector & drivingNoise, 
    const Equation & euqation)
{
    return 0.0;
}

double exercises::milsteinStep(double dVal, double dTime,
    const DVector & drivingNoise,
    const Equation & euqation)
{
    return 0.0;
}
```

## Exercise 3

For exercise 3 we'll need to define the function
`exercises::MonteCarlo3`,
which is declared in [Practical02Exercises.hpp](./Practical02Exercises.hpp).

```c++
/* Includes ... */ 

namespace exercises
{
    /* Typedefs... */
    /* Step Functions... */

    /** Monte Carlo result structure */
    struct MCResult {
        double mc_estimate; // Monte Carlo estimate
        double mc_stdev;    // Monte Carlo standard deviation
    };

    /** MonteCarlo3 - corresponding to the scalar SDE
                      dS(t)=a(t,S(t))dt+b(t,S(t))dB(t)
    * @param dS0 initial stock price
    * @param dT time to maturity
    * @param dR riskfree interest rate
    * @param equation contains the coefficient functions e.g. (a,b) or (a,b,b')
    * @param numericalStep defines the numerical scheme e.g. eulerstep or milsteinStep
    * @param iNumberOfSteps number of steps (of equal length) taken by the method
    * @param iNumberOfPaths number of trajectories generated
    * @param payoffFunction defines the payoff
    * @return a struct with two entries, the first is the Monte Carlo estimate of the price, 
            the second is the estimated stdev of the MC estimate
    */
    MCResult MonteCarlo3(double dS0,
        double dT,
        double dR,
        Equation const& equation,
        NumericalStep const& numericalStep,
        unsigned long int iNumberOfSteps,
        unsigned long int iNumberOfPaths,
        PayoffFunction const& payoffFunction);
}
```

As these are functions that return `double`,
we can write a dummy implementation by returning `0.0`.

Note that `exercises::MonteCarlo3` returns an 
`MCResult` just like
**Practical01**'s `exercises::MonteCarlo2`,
so we can use a similar dummy implementation.

We first create a C++ file, which I'll call
**MonteCarlo.cpp**, inside of
**CppCourse/Practicals/Practical02/Src**.

We need to include the header file, 
so we copy the include from 
[Practical02.cpp](Src/Practical02.cpp).
```c++
#include "Practical02/Practical02Exercises.hpp"
```

Then we implement `exercises::MonteCarlo3`,
making sure that it's inside the `exercises` namespace.

```c++
#include "Practical02/Practical02Exercises.hpp"

namespace exercises {

    MCResult MonteCarlo3(double dS0,
        double dT,
        double dR,
        Equation const& equation,
        NumericalStep const& numericalStep,
        unsigned long int iNumberOfSteps,
        unsigned long int iNumberOfPaths,
        PayoffFunction const& payoffFunction)
    {
        // TODO: Implement!
        return MCResult{0.0, 0.0};
    }
}
```

Recall that `MCResult` is a struct, 
which is like an object that only contains 
"structured" data, no methods or functions.

This data can be accessed like we would access
the internal data of objects; so this would be an
alternative dummy implementation.

```c++
#include "Practical02/Practical02Exercises.hpp"

namespace exercises {

    MCResult MonteCarlo3(double dS0,
        double dT,
        double dR,
        Equation const& equation,
        NumericalStep const& numericalStep,
        unsigned long int iNumberOfSteps,
        unsigned long int iNumberOfPaths,
        PayoffFunction const& payoffFunction)
    {
        // TODO: Implement!
        
        // Return the estimate and standard deviation.
        MCResult result;
        result.mc_estimate = 0.0;
        result.mc_stdev = 0.0;
        return result;
    }
}
```

## Exercise 4

Exercise 4 has a large amount of functions to define,
pretty much all operations with Complex numbers,
the good thing is that each of these should be
relatively simple, and we're given plenty of examples
of how to implement these.

The declarations are in 
[ComplexNumber.hpp](./ComplexNumber.hpp),
while some definitions we can use as examples are in
[ComplexNumber.cpp](./Src/ComplexNumber.cpp).

I'll add some comments to the header file,
`// !` means we'll have to define them,
whereas `// Already defined!` means it's already
defined and we can use it as an example.

```c++
class ComplexNumber
{
public:

    // Constructors
    ComplexNumber(); // Already defined!
    explicit ComplexNumber(double , double=0.0); // Already defined!

    // Incremental Operators using other complex numbers.
    ComplexNumber & operator+=(const ComplexNumber &); // Already defined!
    ComplexNumber & operator-=(const ComplexNumber &); // !
    ComplexNumber & operator*=(const ComplexNumber &); // !
    ComplexNumber & operator/=(const ComplexNumber &); // !

    // Incremental operators using real numbers.
    ComplexNumber & operator+=(const double &); // !
    ComplexNumber & operator-=(const double &); // !
    ComplexNumber & operator*=(const double &); // !
    ComplexNumber & operator/=(const double &); // !

    // Print statement
    std::ostream & print(std::ostream &) const; // Already defined!

private:
    double dRe_;
    double dIm_;
};

// Binary operators Complex + Complex
ComplexNumber operator+(const ComplexNumber &,const ComplexNumber &); // Already defined!
ComplexNumber operator-(const ComplexNumber &,const ComplexNumber &); // !
ComplexNumber operator*(const ComplexNumber &,const ComplexNumber &); // !
ComplexNumber operator/(const ComplexNumber &,const ComplexNumber &); // !

// Binary operators Complex + Real
ComplexNumber operator+(const ComplexNumber &,const double &); // !
ComplexNumber operator-(const ComplexNumber &,const double &); // !
ComplexNumber operator*(const ComplexNumber &,const double &); // !
ComplexNumber operator/(const ComplexNumber &,const double &); // !

// Binary operators Real + Complex
ComplexNumber operator+(const double &,const ComplexNumber &); // !
ComplexNumber operator-(const double &,const ComplexNumber &); // !
ComplexNumber operator*(const double &,const ComplexNumber &); // !
ComplexNumber operator/(const double &,const ComplexNumber &); // !

// "Print" statement using std::cout << my_complex_number;
std::ostream & operator<<(std::ostream &, const ComplexNumber &); // Already defined!
```

As you can see, we mainly need to define
incremental operators such as `-=`
and binary operators such as `-`, 
and in each of these cases we're given an example.

We first create a C++ file, which I'll call
**ComplexNumberSolutions.cpp**, inside of
**CppCourse/Practicals/Practical02/Src**.

We need to include the header file, 
so we copy the include from 
[ComplexNumber.cpp](Src/ComplexNumber.cpp).
```c++
#include "Practical02/ComplexNumber.hpp"
```

We first have a look at the implementation
example of `ComplexNumber::operator+=` in
[ComplexNumber.cpp](Src/ComplexNumber.cpp).

```c++
ComplexNumber & ComplexNumber::operator+=(const ComplexNumber & cnArg)
{
    dRe_ += cnArg.dRe_;
    dIm_ += cnArg.dIm_;
    return *this;
}
```

I'll explain what the `&` means later,
but for now it is fairly clear how we would be
able to modify this to define operator `-=`
instead; inside our **ComplexNumberSolitions.cpp**
we write

```c++
#include "Practical02/ComplexNumber.hpp"

// Incremental operators with complex numbers
ComplexNumber & ComplexNumber::operator-=(const ComplexNumber & cnArg)
{
	dRe_ -= cnArg.dRe_;
	dIm_ -= cnArg.dIm_;
	return *this;
}
```

I'll let you figure out `*=` and `/=` but
they're pretty much the same (of course,
this is complex number multiplication 
and division, which is not term-wise).

Nexto would be `ComplexNumber::operator+=`
where the input is a `double` instead of
a `ComplexNumber`, the idea is that this
`double` represents a real number

```c++
#include "Practical02/ComplexNumber.hpp"

/* Incremental operators with complex numbers... */

// Incremental operators with real numbers
ComplexNumber & ComplexNumber::operator+=(const double & value) {
    dRe_ += value;
    return *this;
}
```

Next would be the binary operators,
for which we have `operator+` as an example in 
[ComplexNumber.cpp](./Src/ComplexNumber.cpp).

```c++
ComplexNumber operator+(const ComplexNumber & Arg1,
            const ComplexNumber & Arg2)
{
    ComplexNumber Res(Arg1);
    return Res +=Arg2;
}
```

As you can see, these binary operators can be
created using the incremental operators we've already
defined! In our file we can add;

```c++
#include "Practical02/ComplexNumber.hpp"

/* Incremental operators with complex numbers... */
/* Incremental operators with real numbers... */

// Binary operators Complex + Complex
ComplexNumber operator-(const ComplexNumber & Arg1,
            const ComplexNumber & Arg2)
{
    ComplexNumber Res(Arg1);
    return Res -=Arg2;
}
```

And, well for Complex + Real and Real + Complex
this turns out to be rather straightforward;
precisely because the constructor can take
either a complex number or a real number,
and because the incremental operators have
already been defined for both complex and
real numbers.


```c++
#include "Practical02/ComplexNumber.hpp"

/* Incremental operators with complex numbers... */
/* Incremental operators with real numbers... */
/* Binary operators Complex + Complex */

// Binary operators Complex + Real
ComplexNumber operator+(const ComplexNumber & Arg1,
            const double & Arg2)
{
    ComplexNumber Res(Arg1);
    return Res +=Arg2;
}

// Binary operators Real + Complex
ComplexNumber operator+(const double & Arg1,
            const ComplexNumber & Arg2)
{
    ComplexNumber Res(Arg1);
    return Res +=Arg2;
}
```


# Extra

If you've made it this far, you should
be able to setup Practical02.

In this section I'll give some explanation on 
the declarations inside 
[ComplexNumber.hpp](./ComplexNumber.hpp).

## Constructors
`ComplexNumber` is a class, 
and we can create new objects, 
or instances of this class,
by using the constructors.

```c++
// In ComplexNumber.hpp, inside class ComplexNumber
ComplexNumber();

// In ComplexNumber.cpp
ComplexNumber::ComplexNumber() : dRe_(0.0), dIm_(0.0) {}
```

This is the default constructor,
you can directly initialize the member variables
of your object by using the notation above,
it is also possible to do further initialization steps
inside the `{}`.

You can call this default constructor with `ComplexNumber z;`

```c++
// In ComplexNumber.hpp, inside class ComplexNumber
explicit ComplexNumber(double , double=0.0);

// In ComplexNumber.cpp
ComplexNumber::ComplexNumber(double dReArg, double dImArg) 
	: dRe_(dReArg), dIm_(dImArg) {}
```

This is the constructor that take one or two real values
$(a, b)$ and return the complex number 
$a+bi$, where if only one real value is given,
the complex number returned has zero imaginary part.

The `..., double=0.0)` part is where the
default value of the function is given when
only one parameter is given.

The `explicit` keyword works as such; in C++, 
the compiler is allowed to do one implicit conversion,
so for example if you call a function that requires
a `ComplexNumber` and give it a `double`,
and you have an implicit way of converting `double`
into `ComplexNumber`, the compiler will do
this implicit conversion.
The `explicit` keyword makes sure that the compiler
cannot use this constructor for implicit conversions.

The definition of the constructor itself is similar to 
the standard constructor.

You can use this constructor as follows;
```c++
ComplexNumber x = ComplexNumber(1.0, 2.0);
ComplexNumber y(1.0, 2.0);
```

## Incremental operators

```c++
// In ComplexNumber.hpp, inside class ComplexNumber
ComplexNumber & operator+=(const ComplexNumber &);
```

This defines a method (function of a class)
that takes a `const ComplexNumber &`
and returns a `ComplexNumber &`.

If we let `a` and `b` be complex numbers, then
```c++
ComplexNumber c = ( a += b );
```

will call `a.operator+=(b)`, which increments `a` by
`b`, without ever changing `b`, and then 
returns `a` itself 
(so `c` and `a` end up having the same value).

Why does `operator+=` return the initial object?
This is so that the operator can be chained,
this is more evident in the `operator>>` case, 
where at each point the operator returns 
`std::cout` to be able to chain it.

```c++
// Though chaining, this...
std::cout >> "Hello" >> " World!" >> '\n';

// Becomes this...
((std::cout >> "Hello") >> " World!") >> '\n';
```

Now... about the `&`, 
these here mean that we have references.
This means that we won't be making copies of the data,
but referring directly to where the data is.
This increases performance, 
but returning a reference can also be very powerful. 

For example, the `std::vector` has a method
`at` which returns a reference to the nth 
element, this means we can write code like this;

```c++
// Create a vector of integers...
std::vector<int> v {0, 1, 2, 3, 4, 5, 6};

// Increase the 3rd element by 4
v.at(2) += 4;

// Print the 3rd element
std::cout << v.at(2) << std::endl;
```

If the `at` method returned an `int`
instead of an `int &`, 
then we wouldn't be able to change the 
elemts of `v` through the `at` method.

> What's the difference between 
> `v.at(100)` and `v[100]`?
> The `at` method has bounds checks, 
> making sure that you don't access elements outside
> the vector.
> On the other hand, `v[100]` will either throw an
> error, give you access to random data, or
> return 0, all depending on which 
> compiler you happen to have.

Finally, the input is a `const ComplexNumber &`,
this means that it's a constant reference.
Like a reference, we don't copy the data, 
which is good for performance.
However, since it's constant, 
we also promise not to make any changes to it!

## The print function

```c++
// In ComplexNumber.hpp, inside class ComplexNumber
std::ostream & print(std::ostream &) const;
```

This function takes an `std::ostream` by reference
(which is an output stream, such as `std::cout`),
and returns an output stream by reference.

In practice, it should take `std::cout`,
use it to print stuff, and then return it.

Which is exactly what happens in 
[ComplexNumber.cpp](./Src/ComplexNumber.cpp),
if we recall that `<<` takes an output 
stream on the left,
something else on the right, 
and returns the output stream.


```c++
// In ComplexNumber.cpp
std::ostream & ComplexNumber::print(std::ostream & os) const
{
	return os << "(" << dRe_ << ", " << dIm_ << "i)";
}
```

But there's still one thing that isn't clear...
what is `const` doing at the end of the declaration?

```c++
// In ComplexNumber.hpp, inside class ComplexNumber
std::ostream & print(std::ostream &) const;
```

For methods (member functions of an object),
the method is `const` if it does not change the
internal state of the object.

All of the incremental operators do change
the internal state of our `ComplexNumber`,
however, the printing function should just
look at the object without changing it,
which is why it's a `const` method.

## Binary operators

```c++
// In ComplexNumber.hpp, outside class ComplexNumber
ComplexNumber operator+(const ComplexNumber &,const ComplexNumber &);
```

I'll just note that these binary operators are 
defined outside of the class definition.
This is because maybe we want to define
`double` + `ComplexNumber` without having to
make changes to the `double` class 
(which isn't even possible, I think?)
Or to define `std::ostream << ComplexNumber`
without having to make changes to the
`std::ostream` class.

We're also no longer returning a `ComplexNumber &`,
instead we're returning just a `ComplexNumber`,
because we're creating a new complex number instead
of modifying the input complex numbers.

## Printing operator

```c++
// In ComplexNumber.hpp, outside class ComplexNumber
std::ostream & operator<<(std::ostream &, const ComplexNumber &);

// In ComplexNumber.cpp
std::ostream & operator<<(std::ostream & os, const ComplexNumber & cnArg)
{
    return cnArg.print(os);
}
```
This is defining the `std::ostream << ComplexNumber`
binary operator, which lets us print ComplexNumbers
using the
`std::cout << my_complex_number;` syntax.

In this case it's using the print method defined 
earlier, but it can often be defined directly.

It just needs to be a `operator<<`
that takes and returns an `std::ostram&`,
together with nother type of value.



Here's another example of how we might be able to 
create a print method for vectors,

```c++
#include <iostream>
#include <vector>

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& vec) 
{
    // The first term does not have a comma before it 
    bool first = true;

    // Start the vector with [
    os << '[';

    // Loop over the values inside the vector
    for (const int& value : vec) {

        // The first term does not have a comma before it.
        if (first) { first = false; }
        else { os << ", "; }

        // Print the value
        os << value;
    }

    // End the vector with ]
    os << ']';

    // Return the output stream
    return os;
}

int main()
{
    // Create a vector
    std::vector<int> v {0, 1, 2, 3, 4, 5, 6};

    // Print it
    std::cout << v << '\n'; // [0, 1, 2, 3, 4, 5, 6]

    return 0;
}
```

And here's how we might print an `MCResult`;

```c++
#include <iostream>

struct MCResult {
	double mc_estimate; // Monte Carlo estimate
	double mc_stdev;    // Monte Carlo standard deviation
};


std::ostream& operator<<(
    std::ostream& os, const MCResult& result)
{
    os << "Monte Carlo Result:" << '\n';
    os << '\t' << "Estimate: " << result.mc_estimate << '\n'; 
    os << '\t' << "Standard Deviation: " << result.mc_stdev << '\n'; 
    return os;
}

int main()
{
    // Create an MCResult
    MCResult my_result{4.7, 2.4};

    // Print it!
    std::cout << my_result;
    // Monte Carlo Result: 
    //     Estimate: 4.7
    //     Standard Deviation: 2.4

    return 0;
}
```