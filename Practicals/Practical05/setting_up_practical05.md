# Setting up Practical 05

> **NOTE:** This is the first practical that properly uses boost. 
> Make sure you have boost set up correctly!

This is a markdown file, you can open it in VS Code to se it formatted nicely
and use its links.

For the links to work correctly, you'll need to place this file inside
the **CppCourse** > **Practicals** > **Practical05** folder you get in step 1.
You can place it elsewhere inside **CppCourse** in the meantime.

## The Practical05 folder

Go to the [course site](https://courses.maths.ox.ac.uk/course/view.php?id=5974),
and click on **Practical exercises** to download the
**Practicals.zip** file.
Extract this and inside you'll find **Practical05.zip**
along with the other practicals.
Extract **Practical05.zip** and you'll get a **Practical05** folder.

Place the **Practical05** inside **CppCourse** > **Practicals**.

The folder structure of **CppCourse** should end up looking like this.

```
CppCourse
├─ boostRoot
├─ ...
├─ Practicals
│  ├─ Practical01
│  ├─ ...
│  ├─ Practical04
│  └─ Practical05
│     ├─ Src
│     ├─ ...
│     └─ Practical05Exercises.hpp 
└─ CMakeLists.txt
```

As an optional step, place this file inside the **Practical05** folder,
which would then look like this

```
Practical05
├─ Src
│  └─ Practical05.cpp
├─ BitManipTests.hpp
├─ CMakeLists.txt
├─ CppProblemSheet05.pdf
├─ Practical05_output.txt
├─ Practical05Exercises.hpp
└─ setting_up_practical04.md
```

If you do, you should be able to click on
[this link to open CppProblemSheet5.pdf](./CppProblemSheet05.pdf)

## Enabling Practical05 in the global CMake file.


Go to the
[global CMakeLists.txt file](../../CMakeLists.txt),
and enable Practical05 by uncommenting the appropriate line,
from:

```cmake
# Practicals and solutions
#...
add_subdirectory(Practicals/Practical04)
#add_subdirectory(Practicals/Practical04Solutions)
#add_subdirectory(Practicals/Practical05)
#add_subdirectory(Practicals/Practical05Solutions)
```

To

```cmake
# Practicals and solutions
#...
add_subdirectory(Practicals/Practical04)
#add_subdirectory(Practicals/Practical04Solutions)
add_subdirectory(Practicals/Practical05)
#add_subdirectory(Practicals/Practical05Solutions)
```

Once you reload the CMake Project,  
you should be able to select the `Practical05` project  in the top bar,
and try to build and run it
(which at this point should have errors).

> **Note:** This is the first practical that uses gtest, 
> so the Practical05 might be at the very bottom of the list of
> configurations, and will have a different symbol.


## Setting up our C++ files

We need to implement the following functions 
(everything in [Practical05Exercises.hpp](./Practical05Exercises.hpp));

- `exercises::subtract`
- `exercises::swap`
- `exercises::Regression`
- `exercises::Projection`
- `exercises::EuropeanOptionPricer::EuropeanOptionPricer`
- `exercises::EuropeanOptionPricer::operator()`
- `exercises::MonteCarlo4`

It'd make sense to put the bit manipulation functions 
from exercise 5 together,
the implementaiton of the EuropeanOptionPricer class
in its own file, 
and each of the other files separately.

## Dummy implementations

Most of the files are implementing functions and methods
declared in [Practical05Exercises.hpp](./Practical05Exercises.hpp),
so we always start their implementation files with
an include statement for this header file,
and I recommend implementing things inside of the namespace
`exercises`.

```c++
#include "Practical05/Practical05Exercises.hpp"

namespace exercises {
    // ...
}
```

### Exercise 1: Regression

From the description of the exercise, 
there are $N$ `y_Vals`,
while there are $r$ `testFunctions`.
The return value of our function is the regression coefficients,
of which there are $r$,
and which are inside of an `exercises::BVector`,
which is a boost vector of doubles;
```c++
typedef boost::numeric::ublas::vector<double> BVector; // boost vector of doubles
```

We go check the documentation for 
[Boost Vectors](https://beta.boost.org/doc/libs/1_82_0/libs/numeric/ublas/doc/vector.html).

There we find that 
- `vector (size_type size)` *Allocates an uninitialized `vector` that holds `size` elements.*

So we can use this constructor for our dummy implementation.

```c++
// Inside namespace exercises...
/** Regression computes regression coefficients
* @param yVals observed y values
* @param factors explanatory factors corresponding to observed y values
* @param testFunctions vector of test functions
* @return regression coefficients
*/
BVector Regression(const BVector & yVals,
           const std::vector<BVector> & factors,
           const FVector & testFunctions) {
    BVector result(factors.size());
    return result;
}
```

If we browse the documentation for
[Boost Vectors](https://beta.boost.org/doc/libs/1_82_0/libs/numeric/ublas/doc/vector.html)
a bit more, we might find that Boost also has "zero vectors",
digging up what they are online, they behave like zero vectors
but have technically no data inside of them.

An "uninitialized" vector may have only zeros, but depending on the compiler
this may or may not be guaranteed.
Having our dummy implementation return a zero vector might
alleviate any concerns we have;
```c++
BVector Regression(const BVector & yVals,
       const std::vector<BVector> & factors,
       const FVector & testFunctions) {
    return boost::numeric::ublas::zero_vector<double> (factors.size());
}
```

### Exercise 2: Projection

As with any function which returns a `double`,
we can just return 0.


### Exercise 3: European Option Pricer

Now we're implementing a class! 
It's our first time implementing one
where there's no example implementations for us,
but it should still be similar to previous class implementations
we've worked on.


The constructor won't need to return anything, so we can leave it empty.
I recommend using `namespace exercises` as otherwise you'll
need to change all the `BVector` for `exercises::BVector` and so on.

```c++
// Inside namespace exercises...
/** EuropeanOptionPricer constructor, initialises data members
* @param factorsAt0 gird of factor values at time 0
* @param valuesAtT discounted option payoff at maturity, corresponding
* @param testFunctions set of test functions uded for projection
* @return regressed value
*/
EuropeanOptionPricer::EuropeanOptionPricer(const std::vector<BVector> & factorsAt0,
             const BVector & valuesAtT,
             const FVector & testFunctions) {
    // TODO: Implement constructor
}
```

The only other thing declared in the `EuropeanOptionPricer`
is its `operator()`, which should return a `double`.
So we can implement the dummy solution as follows;
```c++
// Inside namespace exercises...
/** operator() option pricer
* @param factorsAt0 gird of factor values at time 0
* @param testFunctions vector of test functions
* @param coefficients regression coefficients
* @return regressed value
*/
double EuropeanOptionPricer::operator()(const BVector & factorAt0) {
    // Todo: implement operator()
    return 0.0;
}
```

### Exercise 4: MonteCarlo4

Once again, we must return a Boost vector.
We can use a similar strategy as we did for Exercise 1.
What is the length of the vector?
Reading Exercise 4, the Boost vector we return must be
of the same length as `vS0`, 
which is a standard vector of boost vectors.

```c++
// Inside namespace exercises...
/** MonteCarlo4 - given a grid of initial stock values (2D GBM), generates a set of possible corresponding payoffs
* @param vS0 an std vector of initial factors
* @param dR riskfree rate
* @param dSigma1 vol of the first component
* @param dSigma2 vol of the second component
* @param dRho correlation of driving BM components
* @param dT time to maturity
* @param payoff payoff function
* @return regressed value
*/
BVector MonteCarlo4(std::vector<BVector> vS0,
            double dR,
            double dSigma1,
            double dSigma2,
            double dRho,
            double dT,
            Function const& payoff) {
    BVector result(vS0.size());
    return result;
}
```

## Exercise 5: Bit Manipulation

> **Note:** At this point, you should be able to build the project and have it
> compile. This is because even if the bit manipulation functions
> have not yet been implemented, they are not tested either,
> because we're for the first time writing our own tests!

Exercise 5 is about two things;
- using bit manipulations;
- writing tests with **gtest**.

Our dummy implementations in this case can be
implementations that don't use bit manipulation.
This way we can test *our tests* first,
make sure those tests work alright... 
then write the bit manipulation versions of our functions.

For example, this could be our dummy implementation of `exercises::subtract`;

```c++
// Inside namespace exercises...
/** Computes a-b using bitmanipulation operations only
* @param a
* @param b
* @return a-b
*/
unsigned int subtract(unsigned int a, unsigned int b) {
    // TODO: Replace this with an implementation using bit manipulation operations!
    return a - b;
}
```

And this could be a dummy implementation of `exercises::swap`,
which uses a temporary variable, so would not work with the requirements
of the exercise *"[...] and strictly without any additional temporary variables"*;

```c++
// Inside namespace exercises...
/** Swaps the values of two arguments using bitmanipulation operations only,
* and without and additional temp variables.
* @param a
* @param b
*/
void swap(unsigned int & a, unsigned int & b) {
    // TODO: Replace this with an implementation using bit manipulation operations!
    unsigned int c = b;
    b = a;
    a = c;
}
```

Finally, let's add a dummy test to [BitManipTests.hpp](./BitManipTests.hpp);
```c++
#ifndef __PRACTICAL05_TEST_HPP__
#define __PRACTICAL05_TEST_HPP__

#include "gtest/gtest.h"
#include "Practical05/Practical05Exercises.hpp"

TEST(DummyTests, Equality) {
    int my_num = 5;
    EXPECT_EQ(6, my_num);
}

#endif //PRACTICAL05_TEST_HPP
```

You can have a look at the documentation for gtest 
[here](https://google.github.io/googletest/primer.html),
where I found how to use gtest.
There's also examples in 
[Lecture10](../../Lectures/Lecture10/BitManipTests.hpp).





# Extra topics

You should be able to get started on the exercises with everything before this, 
here's some extra information you may or may not find useful.


## What are we doing in Exercises 1-4?

The description of what we're doing is split among the four exercises,
I'll try to summarize it here.

The goal is to construct an estimate of the conditional 
expectation $V(x)$,

$$ V(x) = \mathbb{E}[f(X_{t_1}) \,| \, 
X_{t_0} = x] \approx \sum_{i=1}^r \phi_i(x) \beta_i .$$

This approximation formula, involving $\phi_i$,
$x$ and $\beta_i$, is calculated in Exercise 2's 
`exercises::Projection`.


> **Note:** The maths behind this is explained in Lecture 15 of the course,
> you might be able to have a look at the lecture notes if you wish.

### Factors, factors at 0.

Each $x$, $X$, and $X^{(i)}_{t_0}$ is made of a vector of data, 
$X= (X_1, \ldots, X_2)$,
this is a Boost vector
- In `exercises::Projection`, `const BVector & factor` is this $x$.
- In `exercises::EuropeanOptionPricer`, 
the `const std::vector<BVector> & factorsAt0` is a standard
vector of $X^{(i)}_{t_0}$, which are samples.
- In `exercises::MonteCarlo4`, the `std::vector<BVector> vS0`
is similarly a set of samples. 

In [Practical05.cpp](./Src/Practical05.cpp),
this is built in the `vS0` variable.
You'll notice that in this case $k=2$, 
and each $X$ is made of two parameters.
Practical05 builds $200^2$ initial $X^{(i)}_{t_0}$,
with the parameters forming a 2D grid around $(1,1)$
of width $0.25$.

```c++
// In Practical05.cpp ...
//constructing initial grid
unsigned int n(200);
double dDS(0.25/n);
double dS01(0.875), dS02(0.875);
double dR(0.1), dSigma1(0.2), dSigma2(0.08), dRho(-0.7), dT(1.0);

std::vector<BVector> vS0(n*n);
BVector vTemp(2);
unsigned int k(0);
for(unsigned int i=0; i<n; ++i, dS01+=dDS)
{
    double dS2(dS02);
    for(unsigned int j=0; j<n; ++j, dS2+=dDS, ++k)
    {
        vTemp[0]=dS01;
        vTemp[1]=dS2;
        vS0[k]=vTemp;
    }
}
```

### Test functions

Let's look at the $\phi_i$. 
Each $\phi_i$ is a function that takes a Boost vector without
changing it, and returns a `double`. These are of type `Function`

Then all of the $\phi_i$ are placed together in a standard vector,
of type `FVector`.

```c++
typedef std::function<double(const BVector &)> Function; // type of test function
typedef std::vector<Function> FVector; // std vector of test functions
```

In all of `exercises::Regression`, `exercises::Projection`,
and `exercises::EuropeanOptionPricer`, the `\phi` are in the
`testFunctions` argument.

```c++
const FVector & testFunctions
```

Note that you're supposed to save these test functions
during the `EuropeanOptionPricer`'s constructor
into the `m_TestFunctions` member variable,
so that you can access them when you need them in
`EuropeanOptionPricer::operator()`.

You can see the `testFunctions` vector being initialized in
[Practical05.cpp](./Src/Practical05.cpp),
```c++
//set of test functions
FVector testFunctions;
testFunctions.push_back(Const);
testFunctions.push_back(X1_1);
// ...
testFunctions.push_back(X12_22);
testFunctions.push_back(Basket);
```

Where it's adding each of the functions defined
earlier in [Practical05.cpp](./Src/Practical05.cpp),
```c++
double Const(const BVector & vArg){return 1.0;}
double X1_1(const BVector & vArg){return vArg[0];}
double X1_2(const BVector & vArg){return vArg[0]*vArg[0];}
double X1_3(const BVector & vArg){return vArg[0]*vArg[0]*vArg[0];}
double X2_1(const BVector & vArg){return vArg[1];}
double X2_2(const BVector & vArg){return vArg[1]*vArg[1];}
double X2_3(const BVector & vArg){return vArg[1]*vArg[1]*vArg[1];}
double X12_11(const BVector & vArg){return vArg[0]*vArg[1];}
double X12_12(const BVector & vArg){return vArg[0]*vArg[1]*vArg[1];}
double X12_21(const BVector & vArg){return vArg[0]*vArg[0]*vArg[1];}
double X12_22(const BVector & vArg){return vArg[0]*vArg[0]*vArg[1]*vArg[1];}
double Basket(const BVector & vArg){return max(vArg[0],vArg[1]);}
```

As you can see these test functions take our $x$, 
which is a `BVector` with two parameters, 
and return something about them that is a double,
like `X12_12` returning the first parameter times the second squared.

### Coefficients $\beta_i$

The coefficients $\beta_i$ are the last ingredient we would need
to build $V(x)$,
and in `exercises::Projection` they are the argument
```c++
const BVector & coefficients
```

The question is how do we get these coefficients?
This is what we build `exercises::Regression` for.

We use the matrix formula
$$\beta = (\Phi^T \Phi)^{-1} \Phi^T Y,$$
where $Y$ is the `const BVector & yVals` argument,
and $\Phi$ is a matrix built from the
test functions and the sample factors.


### Sample

The last missing piece to construct the $V(x)$
estimate is an initial sample 
$\{X_{t_0}^{(1)},\ldots, X_{t_0}^{(N)}\}$
together with the observed values at time 1, $Y$,
which is
$\{f(X_{t_1}^{(1)}),\ldots, f(X_{t_1}^{(N)})\}$,
where $f$ is the payoff function.

How are we going to generate this initial sample?
With Monte Carlo methods! 

In `MonteCarlo4`, we simulate a stock pair $(S_1, S_2)$.

We are given a grid of initial stock values in `vS0`
(Same `vS0` as before), these are the $X_{t_0}^{(i)}$. 

For each of these, we simulate the stock and get
$X_{t_1}^{(i)}$, then we calculate the payoff
with `Function const& payoff`,
we take into account the discount factor
(the question mention the function *"returns a boost vector 
of **discounted** simulated payoff values"*).

We put all of these into a `BVector` which should end up
being the same size as `vS0`, and we should be good.


### Summary

Exercise 1: We calculate the coefficients $\beta_i$ for the
estimate $V(x)$.

Exercise 2: We give the estimate $V(x)$ given the coefficients.

Exercise 3: We make an object that you initialize once,
calculating the coefficients, and then can use as many
times as we want as our $V(x)$ function.

Exercise 4: We simulate stocks using MonteCarlo methods
to create the data we need to use Regression
to find the coefficients $\beta_i$.

I recommend starting with Exercise 2, as calculating
the estimate once we have the coefficients is relatively straightforward.

Then I recommend trying Exercise 3; assuming your
Regression and Projection functions worked, 
you'll need to wrap them into an object that
finds the coefficients in its constructor, remembers them,
and uses them to calculate the estimate as many times as we want.

Exercise 1 is a bit more challenging since it's the first time
we're using matrix operations in the boost library, I have a few comments on
this in a bit.

Exercise 4 is slightly similar to previous Monte Carlo functions we've seen
in the parts where the stock is simulated; however this time we don't
need to calculate the mean or standard deviation, and 
while $S^1_t$ satisfies the stochastic differential equation for
geometric brownian motion we've seen in previous Monte Carlo examples, 
you'll have to solve the stochastic
differential equation for $S^2_t$, to be able to simulate it.
$$\mathrm{d}S^2_t = r S^2_t \mathrm{d}t + \sigma_2 S^2_t 
\left(\rho \mathrm{d}B^1_t + \sqrt{1-\rho^2} \mathrm{d}B^2_t\right).$$



## Using Boost's uBlas: Basic Linear Algebra 

All the linear algebra you need to do is in Lecture09,
especially in the part where the lecturer shows how to solve a system of linear
equations. 
In particular, [in this cpp file](../../Lectures/Lecture09/Src/Lecture09.cpp).

```c++
void exampleLinearEquation(){
  BMatrix A(2,2);
  A(0,0)=1;
  A(0,1)=1;
  A(1,0)=1;
  A(1,1)=0;
  BVector b(2);
  b(0)=5;
  b(1)=2;
  cout << "A=" << A << endl;
  cout << "b=" << b << endl;
  //solving Ax=b
    boost::numeric::ublas::lu_factorize(A);
  cout << "A=" << A << endl;
  boost::numeric::ublas::lu_substitute<const BMatrix,BVector>(A,b);
  cout << "b=" << b << endl;
  //solving A*Ainv=Identity
    BMatrix Ainv(boost::numeric::ublas::identity_matrix<double>(2));
  cout << "Ainv=" << Ainv << endl;
  boost::numeric::ublas::lu_substitute<const BMatrix,BMatrix>(A,Ainv);
  cout << "Ainv=" << Ainv << endl;
}
```

The key functions here are `lu_factorize` and `lu_substitute`.

I usually recommend looking for the documentation to understand what these do,
unfortunately *there does not seem to be official documentation 
for these functions*.

The lecturer's lecture notes are pretty good at explaining what's going on
relative to other guides I've found.

Overall the idea is to factorize a matrix into an upper triangular and 
a lower triangular matrix with `lu_factorize`,
then use this decomposition to solve the system of linear equations in
`lu_substitute`.

The idea though, is that instead of having two matrices which are
half empty in the upper and lower decomposition,
instead the data of this decomposition is overwritten on the
initial matrix, half of it being the upper and half of it being the lower.
This is done by `lu_factorize`, and `lu_substitute` expects the matrix
it is given to be the "two triangular matrices in a trench-coat"
obtained by using `lu_factorize`.


I did notice the following in the documentation for uBlas;

> Q: Should I use uBLAS for new projects?
> 
> A: At the time of writing (09/2012) there are a lot of good 
> matrix libraries available, e.g., MTL4, armadillo, eigen. 
> uBLAS offers a stable, well tested set of vector and matrix classes, 
> the typical operations for linear algebra and solvers for triangular 
> systems of equations. uBLAS offers dense, structured and sparse matrices;
> all using similar interfaces. 
> And finally uBLAS offers good (but not outstanding) performance. 
> On the other side, the last major improvement of uBLAS was in 2008 
> and no significant change was committed since 2009. 
> 
> So one should ask himself some questions to aid the decision: 
> 
> - Availability? uBLAS is part of boost and thus available in many environments. 
> - Easy to use? uBLAS is easy to use for simple things, 
> but needs decent C++ knowledge when you leave the path. 
> - Performance? There are faster alternatives. 
> - Cutting edge? uBLAS is more than 10 years old and missed 
> all new stuff from C++11. 

... If you plan to do Linear Algebra in your own project, 
many recommend using Eigen these days.
There's been many advances in performance in recent years 
in no small part due to
machine learning relying so much on Linear Algebra.



## Testing

So tests are pretty awesome, and very useful to do.

One of the key strategies of programming is "divide and conquer".
Split what you need to do into different parts, 
then put them all back together.

Sometimes you split functionality into different objects,
sometimes you split it into different functions,
sometimes you split them into different files.

Now, what you can do is **test** every part independently,
make sure they work,
then you can put them all together. 
And you test them again.

This process ensures that if you make a change and 
something is not working anymore, 
then you can run your tests
and see which part of your project is the one that's not working.

This is really useful when you're on your own, but it's
*incredibly useful* when you're working with others.

If the project is split into multiple different parts,
everyone in the team can work on separate things at the same time,
and the tests help make sure everything is working as intended.

### What makes good tests?

Usually you just want to make sure the code you're working on
behaves as expected. Put in some values and check you're getting
what you expect.

Good tests check for many different types of values that a user
might put into your functions. 

For example the tests in Problem Sheet 3 for the last element
were not super useful; sure, it tested 5 different lists of
different length... but all those lists ended in zero!
So our dummy implementation would also pass all those tests,
but as soon as a user uses any list not ending in zero,
they'd be confused if we forgot to implement our function!



## Bit Manipulation?

In Exercise 5 you're also asked to work with bit manipulation,
this exercise is mostly about writing good tests, I think,
but also about getting familiar with the
`&  |  ^  ~  <<  >>`
operators.

These are all about working with your numbers and other data
as if they were sequences of zeros and ones `01101001101`.
So you can think of them as a list of true/false values,
and this operators correspond to;
- `&` Logical and
- `|` Logical or (not exclusive; "A or B or both")
- `^` Logical xor (exclusive or; "either A or B but not both")
- `~` Logical not, ends up flipping zeros and ones.
- `<<` and `>>` are bit shift operators, they shift the sequence left or right.

Right and left shift operators can be used for multiplication 
and division by powers of 2.

### Flags

One way in which bit operations are used is in **flags**. 

Let's say you have a function which can take several ON/OFF 
configuration options, but don't want to pass them each independently
as an argument. What you can do is pass them all together in a single
integer by using flags.

Each flag will be one of these options, and corresponds to a power of 2,
```c++
const int OPTION_A = 1
const int OPTION_B = 2
const int OPTION_C = 4
const int OPTION_D = 8
```

Then, when you want to pass it into a function you'd do something like
```c++
my_function(OPTION_B | OPTION_C | OPTION_D)
```
By using the bitwise or `|`, you're combining the flags into a single integer,
which later in the function you can check for using the bitwise and operator;
```c++
// inside my_function(flags)
if (flags & OPTION_A) { /* Stuff you do if Option A is ON... */ }
if (flags & OPTION_B) { /* ... */ }
if (flags & OPTION_C) { /* ... */ }
if (flags & OPTION_D) { /* ... */ }
```

This is one of the ways `&` and `|` are used in practice.

What can `^` be used for?


