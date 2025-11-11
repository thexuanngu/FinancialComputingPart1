# Setting up practical 04

This is a markdown file, you can open it in Visual Studio Code to se it formatted nicely
and use its links.

For the links to work correctly, you'll need to place this file inside
the **CppCourse** > **Practicals** > **Practical04** folder you get in step 1.
You can place it elsewhere inside **CppCourse** in the meantime.

## 1) The Practical 03 folder

Go to the [course site](https://courses.maths.ox.ac.uk/course/view.php?id=5974),
and click on **Practical exercises** to download the
**Practicals.zip** file.
Extract this and inside you'll find **Practical04.zip**
along with the other practicals.
Extract **Practical04.zip** and you'll get a **Practical04** folder.

Place the **Practical04** inside **CppCourse** > **Practicals**.

The folder structure of **CppCourse** should end up looking like this.

```
CppCourse
├─ boostRoot
├─ ...
├─ Practicals
│  ├─ Practical01
│  ├─ Practical02
│  ├─ Practical03
│  └─ Practical04
│     ├─ Inl 
│     ├─ Src
│     ├─ ...
│     └─ SparseVector.hpp 
└─ CMakeLists.txt
```

As an optional step, place this file inside the **Practical04** folder,
which would then look like this

```
Practical04
├─ Inl
│  └─ Interpolate.inl
├─ Src
│  ├─ Practical04.cpp
│  └─ SparseVector.cpp
├─ BinaryOperators.hpp
├─ CMakeLists.txt
├─ CppProblemSheet4.pdf
├─ Interpolate.hpp
├─ Practical04_output.txt
├─ Practical04Exercises.hpp
├─ setting_up_practical04.md
└─ SparseVector.hpp
```

If you do, you should be able to click on
[this link to open CppProblemSheet4.pdf](../Practical04Solutions/CppProblemSheet04.pdf)


## 2) Enabling Practical03 in the global CMake file.

Go to the
[global CMakeLists.txt file](../../CMakeLists.txt),
and enable Practical03 by uncommenting the appropriate line,
from:

```cmake
# Practicals and solutions
#...
add_subdirectory(Practicals/Practical03)
#add_subdirectory(Practicals/Practical03Solutions)
#add_subdirectory(Practicals/Practical04)
#add_subdirectory(Practicals/Practical04Solutions)
```

To

```cmake
# Practicals and solutions
#...
add_subdirectory(Practicals/Practical03)
#add_subdirectory(Practicals/Practical03Solutions)
add_subdirectory(Practicals/Practical04)
#add_subdirectory(Practicals/Practical04Solutions)
```

Once you reload the CMake Project,  
you should be able to select the `Practical04` project
in the CMake Plugin tab, 
and try to build and run it 
(which at this point should have errors).


## 3) Setting up our `.cpp` file(s)

The [CppProblemSheet04.pdf](../Practical04Solutions/CppProblemSheet04.pdf) 
requests that you upload 
[Practical04_output.txt](../Practical04Solutions/Practical04_output.txt),
**BinaryOperators.cpp**,
[Interpolate.inl](./Inl/Interpolate.inl)
and [SparseVector.cpp](./Src/SparseVector.cpp).

The only new file we need to create is
**BinaryOperators.cpp**, which should be inside 
the **Src** folder.

Inside **BinaryOperators.cpp**,
we include [BineryOperators.hpp](../Practical04Solutions/BinaryOperators.hpp);

```c++
#include "Practical04/BinaryOperators.hpp"
```


## 4) Dummy implementations

Let's first have a look at [Interpolate.inl](./Inl/Interpolate.inl);

```c++
namespace exercises {
    template<typename PreOp, typename PostOp>
    double Interpolate<PreOp,PostOp>::operator()(double dX) const
    {
      return double(); //dummy implementation
    }
}
```
It's already got a dummy implementation! 
There's nothing for us to do at the moment.

Now let's have a look at [SparseVector.cpp](./Src/SparseVector.cpp)

```c++
#include "Practical04/SparseVector.hpp"
//...
std::ostream & exercises::operator<<(std::ostream & os, const SparseVector & svArg) { /* ... */}

SparseVector & exercises::operator+=(SparseVector & svArg1, 
					const SparseVector & svArg2) { /* ... */ }

/*

SparseVector exercises::operator+(const SparseVector & svArg1, 
			const SparseVector & svArg2)
{
	SparseVector res;
	//...
	return res;
}

// ...

*/
```

There's a lot of stuff commented out, if we uncomment them,
we get our dummy implementations for the SparseVector operators.

All that remains is to give dummy implementations to the
class methods in [BinaryOperators.hpp](../Practical04Solutions/BinaryOperators.hpp).
Let's look at `exercises::DF2Yield`, 
which has a method `exercises::DF2Yield::operator()`;

```c++
/** \class DF2Yield
	\brief DF2Yield is a particular binary function object derived from binary_function

	The operator() member takes discount factor and time to maturity and returns the corresponding yield
	*/
class DF2Yield : public std::binary_function<double,double,double>
{
public:
	/** operator() - member function
	  * @param dDiscountFactor discount factor
	  * @param dTimeToMaturity time to maturity
	  * @return continuously compounding yield corresponding to discount factor
	  */
	double operator()(const double dDiscountFactor, const double dTimeToMaturity) const;
};
```

We open our [new BinaryOperators.cpp file](./Src/BinaryOperators.cpp),
and give a dummy implementation.

```c++
#include "Practical04/BinaryOperators.hpp"

// Continuously compounding yield corresponding to discount factor
double exercises::DF2Yield::operator()(const double dDiscountFactor, const double dTimeToMaturity) const {
    // Todo implement!
    return 0.0;
}
```

The class methods we need to implement are;
- `exercises::DF2Yield::operator()`,
- `exercises::Yield2DF::operator()`,
- `exercises::DF2Libor::operator()`,
- `exercises::Libor2DF::operator()`.

Their dummy solutions can be implemented in a similar way.

Once these are implemented, the building process should
give "Build finished" at the end, though it might still give some deprecation warnings (which we can safely ignore).

## 5) Interpolation functions

In [Interpolate.inl](./Inl/Interpolate.inl),
we only need to implement `Interpolate<PreOp,PostOp>::operator()`,
however keep in mind that in this case th class `Interpolate`
has a few extra things that we can use;

Let's look at [Interpolate.hpp](../Practical04Solutions/Interpolate.hpp),

```c++
// ... Inside namespace exercises
template<typename PreOp, typename PostOp>
class Interpolate 
{
public: 
	// ... Typedefs
    // Constructor
	Interpolate(const DVector xVals, const DVector yVals);
	
	// What we need to implement
	double operator()(const double dX) const;

private:
	DVector m_xVals;
	DVector m_yVals;
	PostOp m_postOp;
};

// Constructor implementation
template<typename PreOp, typename PostOp>
Interpolate<PreOp,PostOp>::Interpolate(DVector xVals, 
					DVector yVals)
					: m_xVals(xVals), 
					  m_yVals(yVals.size()),
					  m_postOp(PostOp())
					  
{
	//pre-transformation - done only once
	std::transform(yVals.begin(),yVals.end(),m_xVals.begin(),m_yVals.begin(),PreOp());
}

```

As you can see, the constructor constructs the sequence of 
$(x_i)$ and $(z_i)$ for us in `m_xVals` and `m_yVals` respectively,
which are `std::vector<double>`.
It also stores $f_2$ in `m_postOp`.

With this we should be able to implement $F$, 
which, for $x_i < x < x_{i+1}$
should return
$$f_2\left(z_i + (z_{i+1}-z_i)\frac{x-x_i}{x_{i+1}-x_i},\, x\right).$$




## 6) Sparse Vector

```c++
typedef std::map<unsigned int, double> SparseVector;
```
A sparse vector is a [std::map](https://devdocs.io/cpp/container/map),
taking `unsigned int` as their first parameter,
and `double` as their second parameter.

The idea is that a `SparseVector` is an infinite vector 
which has only finitely many indices which are nonzero,
so our "map" sends unsigned integers to nonzero values,
and the value is implied to be zero if it's not in the map.

Their `operator+=` method has already been implemented,
and we can see it to check how we'd work with it.

```c++
SparseVector & exercises::operator+=(SparseVector & svArg1, 
					const SparseVector & svArg2)
{
	SparseVector::const_iterator sv2Iter=svArg2.begin();
	SparseVector::const_iterator sv2eIter=svArg2.end();
	for( ;sv2Iter!=sv2eIter; ++sv2Iter) 
	{
		SparseVector::iterator sv1Iter=svArg1.find(sv2Iter->first);
		//alternative code for line 26:
		//SparseVector::iterator sv1Iter=svArg1.find((*sv2Iter).first);
		
		//checking if entry does not exist
		if(sv1Iter==svArg1.end() && (sv2Iter->second)!=0.0)
			svArg1.insert(*sv2Iter);
		//alternative code for line 32:
		//svArg1.insert(std::make_pair(sv2Iter->first,sv2Iter->second));
		else if(sv1Iter!=svArg1.end()) //if entry extist, then update 
		{
			sv1Iter->second+=sv2Iter->second;
			if(sv1Iter->second==0.0) //if entry becomes zero, then remove
				svArg1.erase(sv1Iter);
		}
	}
	//return reference to first argument
	return svArg1;
}
```

As you can see,
- One looks through all nonzero elements of `svArg2`
since any zeros do not affect `svArg1`. 
- If the corresponding entry is zero in `svArg1`, we add it
since it's no longer zero.
- Otherwise, we just add them together.
- But we need to check if we end up getting a zero, in
which case the entry has to be removed from our vector.

Iterators will let us "look into" our `std::map`.
- `SparseVector::const_iterator` can be used when the iterator moves around
and looks into the `SparseVector` but doesn't change it.
- `SparseVector::iterator` can be used for when we do change the 
`SparseVector` with our iterator.

Iterators behave like pointers, so we can "increment them"
to move through the entries in the map;
and we can "dereference them" with `*(iterator)`
to get our entries, or we can access the entry's
`first` and `second` directly through
`iterator->first` and `iterator->second`.


