# Setting up Practical 06

This is a markdown file, you can open it in VS Code to se it formatted nicely
and use its links.

For the links to work correctly, you'll need to place this file inside
the **CppCourse** > **Practicals** > **Practical06** folder you get in step 1.
You can place it elsewhere inside **CppCourse** in the meantime.


## The Practical06 folder

Go to the [course site](https://courses.maths.ox.ac.uk/course/view.php?id=5974),
and click on **Practical exercises** to download the
**Practicals.zip** file.
Extract this and inside you'll find **Practical06.zip**
along with the other practicals.
Extract **Practical06.zip** and you'll get a **Practical06** folder.

Place the **Practical06** inside **CppCourse** > **Practicals**.

The folder structure of **CppCourse** should end up looking like this.

```
CppCourse
├─ boostRoot
├─ ...
├─ Practicals
│  ├─ Practical01
│  ├─ ...
│  ├─ Practical05
│  └─ Practical06
│     ├─ Src
│     ├─ ...
│     └─ Practical06Exercises.hpp 
└─ CMakeLists.txt
```

As an optional step, place this file inside the **Practical06** folder,
which would then look like this

```
Practical05
├─ Src
│  ├─ Function.cpp
│  ├─ Payoffs.cpp
│  └─ Practical06.cpp
├─ CMakeLists.txt
├─ CppProblemSheet06.pdf
├─ Definitions.hpp
├─ Function.hpp
├─ IFunction.hpp
├─ Practical06_output.txt
├─ Practical06Exercises.hpp
└─ setting_up_practical06.md
```

If you do, you should be able to click on
[this link to open CppProblemSheet6.pdf](./CppProblemSheet06.pdf)


## Enabling Practical06 in the global CMake file.


Go to the
[global CMakeLists.txt file](../../CMakeLists.txt),
and enable Practical06 by uncommenting the appropriate line,
from:

```cmake
# Practicals and solutions
#...
add_subdirectory(Practicals/Practical05)
#add_subdirectory(Practicals/Practical05Solutions)
#add_subdirectory(Practicals/Practical06)
#add_subdirectory(Practicals/Practical06Solutions)
```

To

```cmake
# Practicals and solutions
#...
add_subdirectory(Practicals/Practical05)
#add_subdirectory(Practicals/Practical05Solutions)
add_subdirectory(Practicals/Practical06)
#add_subdirectory(Practicals/Practical06Solutions)
```

Once you reload the CMake Project,  
you should be able to select the `Practical06` project  in the top bar,
and try to build and run it
(which at this point should have errors).


# Dummy implementations

We need to implement the functions in 
[Practical06Exercises.hpp](./Practical06Exercises.hpp);



- `exercises::PutPayoff`
- `exercises::SpreadOption`
- `exercises::StraddleOption`
- `exercises::BasketPayoff`
- `exercises::AveragePayoff`
- `exercises::SumOfSquares`
- `exercises::InnerProduct`

There's one more function in
[Practical06Exercises.hpp](./Practical06Exercises.hpp),
but `exercises::CallPayoff` has
already been implemented in 
[Payoffs.cpp](./Src/Payoffs.cpp).
We can use this one as an example of how to implement
the other functions... 
but it's also fully implemented instead of a dummy solution,
so let's see how to make a dummy solution.

```c++
// I've used the include headers from Payoffs.cpp in the file where I'll put my implementations.
#include "Practical06/Practical06Exercises.hpp"
#include <algorithm>
#include <numeric>

namespace exercises {
    // I'll put my implementations here    
}
```

Next, I notice that all of the functions we're implementing in this
practical return a `Function`,
which is declared in 
[Function.hpp](./Function.hpp).
I have a look there, 

```c++
class Function
{
public:
    /** Function constructor, initialises m_ifun
    * @param ifunptr smart pointer to IFunction
    */
    explicit Function(IFunPtr ifunptr) : m_ifun(ifunptr) {}
    
    /** Function constructor, initialises m_ifun
    * @param dArg initialises m_ifun to point to the particular IFunctionConst returning dArg
    */
    explicit Function(const double dArg=0.0) : m_ifun(new IFunctionConst(dArg)) {}
    
    //... 
}
```

And notice two constructors 
(there's a third one but let's look at the first two for now).

The first constructor takes an `IFunPtr`,
which is a (shared) pointer to an `IFunction`.
This is the constructor used by `exercises::CallPayoff`,
and probably going to be the constructor you'll use most for your implementations.

However, the second constructor takes a double and seems to return a
constant `Function`, and it even sets this constant to 0 by default,
this constructor is perfect for our dummy implementations.

Here's an example for the `PutPayoff` function,
and you can do something similar for the remaining functions.
```c++
/** PutPayoff put payoff
* @param dK defines the strike
* @param index defines the index of the relevant underlying
* @return Function, such that its operator()(bvArg) returns max(0.0,dK-bvArg[index]);
*/
Function PutPayoff(double dK,BVector::size_type index) {
    return Function();
}
```



# Exercise 1

As this exercise asks you to study what `Function` and `IFunction` 
are on your own, I'll mostly add some extra questions here
to point you towards the right directions.


### What's the difference between Function and IFunction?

Recall that a `std::function<double(BVector)>`
is anything that behaves like a function that takes a 
BVector and returns a double; 
and function objects are objects that
behave like functions by overriding `operator()`.

- Which between `Function` and `IFunction` is a
`std::function<double(BVector)>`?

Have a look at
[Function.hpp](./Function.hpp)
and [IFunction.hpp](./IFunction.hpp);
in particular at their `class` definitions.

- Do they have constructors?
- Do they override `operator()`?
- Is there anything else they do?

Look around
[IFunction.hpp](./IFunction.hpp)
and [Payoffs.cpp](./Src/Payoffs.cpp),

- There seems to be a lot of subclasses of `IFunction`,
but there's no subclasses of `Function`; 
why is this the case?

Finally, I've gone to 
[Practical06](./Src/Practical06.cpp)
and added a line near the end of the main function

```c++
// ...
int main()
{
    // ...
    mystream << "\n";
    
    // This line here!
    ((callPayoff + basketPayoff) - 1.0)(bvArg1);
    
    myfile.close();
    return 0;
}
```

- Why does this line work, and gives no compiler errors?
- What is this line doing?




### Looking at an IFunction.

I recommend you also have a look at the other ones available and
try to understand them.

Here's `IFunctionCoordinate`, from 
[IFunction.hpp](./IFunction.hpp);

```c++
/** \class IFunctionCoordinate
	\brief particular derived class 
	*/
class IFunctionCoordinate : public IFunction
{
public:

    /** IFunctionCoordinate constructor, initialises m_index
    * @param index 
    */
    IFunctionCoordinate(BVector::size_type index=0) : m_index(index) {}

    /** operator() R^k->R function, returns the component of bvARg, with index index m_index
    * @param bvARg vector argument
    * @return component of bvARg, with index index m_index
    */
    double operator()(const BVector & bvArg) const
    {
        return bvArg[m_index];
    }
private:
    BVector::size_type m_index;
};
```

- How would you be able to construct an `IFunctionCoordinate`?
- What are its private member variables used for?
- What does an `IFunctionCoordinate` do?



### Staring into the Abyss that is Function.cpp

It is pretty intimidating to open this file as there's
lots of pre-processor macros.

Here's one of the `operator+=`
```c++
//implementation of operator+=(const Function &)
//this replaces m_ifun with an IBinaryUnaryOp
Function & exercises::Function::operator+=(const Function & fArg)
{
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<plus<double>>>(m_ifun,fArg.m_ifun));
	return *this;
}
```

- What is `IFunctionBinaryComp` doing here?
- Why do we need [std::make_shared](https://devdocs.io/cpp/memory/shared_ptr/make_shared)?

The other `operator+=` uses pre-processor macros...

```c++
//implementation of operator+=(const double)
//this replaces m_ifun with an IFunctionUnaryComp
Function & exercises::Function::operator+=(const double dArg)
{

#if __cplusplus < 201402L 
    // pre C++14	
    m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<IncrementByValue>>(m_ifun,IncrementByValue(dArg)));
#else
    // C++14
    m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<UnaryFunction>>(m_ifun,
        [dArg](double dVal){return dArg + dVal;}));	
#endif

    return *this;
}
```

- Let's say you're using C++14, 
what would this code be transformed into by the preprocessor macro?
- Let's say you're using an older version of C++,
so that `__cplusplus < 201402L`.
What is `IncrementByValue`? Where is it defined?
Is this defined if we are using C++14?

Finally, what is the following??
```c++
[dArg](double dVal) { return dArg + dVal; }
```

While it's not vital for this problem sheet,
you might want to 
[learn about lambda expressions](https://www.programiz.com/cpp-programming/lambda-expression),
which are also known as anonymous functions in other programming languages.


