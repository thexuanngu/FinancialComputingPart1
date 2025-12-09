# Setting up Practical 07

This is a markdown file, you can open it in VS Code to se it formatted nicely
and use its links.

For the links to work correctly, you'll need to place this file inside
the **CppCourse** > **Practicals** > **Practical07** folder you get in step 1.
You can place it elsewhere inside **CppCourse** in the meantime.

> This practical uses the MCLib library that is introduced in the
> last couple of weeks of lectures. 
> The documentation is in **Libraries > MCLibDoc > html > index.html**, which you can open in your browser.
>
> You can also find its documentation
> in the [course's page](https://courses.maths.ox.ac.uk/course/view.php?id=5974),
> by downloading "MCLib html documentation",
> and then opening its `index.html` file with a browser of your choice.


## The Practical07 folder

Go to the [course site](https://courses.maths.ox.ac.uk/course/view.php?id=5974),
and click on **Practical exercises** to download the
**Practicals.zip** file.
Extract this and inside you'll find **Practical07.zip**
along with the other practicals.
Extract **Practical07.zip** and you'll get a **Practical07** folder.

Place the **Practical07** inside **CppCourse** > **Practicals**.

The folder structure of **CppCourse** should end up looking like this.

```
CppCourse
├─ boostRoot
├─ ...
├─ Practicals
│  ├─ Practical01
│  ├─ ...
│  ├─ Practical06
│  └─ Practical07
│     ├─ Src
│     ├─ ...
│     └─ Practical07Exercises.hpp 
└─ CMakeLists.txt
```

As an optional step, place this file inside the **Practical07** folder,
which would then look like this

```
Practical07
├─ Src
│  └─ Practical07.cpp
├─ CMakeLists.txt
├─ CppProblemSheet07.pdf
├─ Practical07_output.txt
├─ Practical07Exercises.hpp
└─ setting_up_practical07.md
```

If you do, you should be able to click on
[this link to open CppProblemSheet7.pdf](./CppProblemSheet07.pdf)




## Enabling Practical07 in the global CMake file.


Go to the
[global CMakeLists.txt file](../../CMakeLists.txt),
and enable Practical06 by uncommenting the appropriate line,
from:

```cmake
# Practicals and solutions
#...
add_subdirectory(Practicals/Practical06)
#add_subdirectory(Practicals/Practical06Solutions)
#add_subdirectory(Practicals/Practical07)
#add_subdirectory(Practicals/Practical07Solutions)
```

To

```cmake
# Practicals and solutions
#...
add_subdirectory(Practicals/Practical06)
#add_subdirectory(Practicals/Practical06Solutions)
add_subdirectory(Practicals/Practical07)
#add_subdirectory(Practicals/Practical07Solutions)
```

Once you reload the CMake Project,  
you should be able to select the `Practical07` project  in the top bar,
and try to build and run it
(which at this point should have errors).


# Dummy Implementations

In this practical we have to implement several classes and a function,
the dummy implementations are relatively straight-forward.

Everything we need to implement is in the namespace `exercises`,
so we can have something like this;

```c++
// In a new C++ file inside Practical07/Src/
#include "Practical07/Practical07Exercises.hpp"

namespace exercises {
    // Our implementations go here...
}
```

We need to implement almost everything inside
[Practical07Exercises.hpp](Practical07Exercises.hpp);

- `basket_payoff::basket_payoff`
- `basket_payoff::operator()`
- `basket_payoff::SizePayoff`
- `geometric_average_payoff::geometric_average_payoff`
- `geometric_average_payoff::operator()`
- `geometric_average_payoff::SizePayoff`
- `half_call_half_put::half_call_half_put`
- `half_call_half_put::operator()`
- `half_call_half_put::SizePayoff`
- `UpRangeOut::UpRangeOut`
- `UpRangeOut::operator()`
- `Val_FDDelta_FDGamma`

(Note that `UpRangeOut::Reset` is already implemented within the header file!)

Let's begin by probably the hardest to implement, but the easiest to write
a dummy implementation of; `Val_FDDelta_FDGamma`. 
This is a `void` function so we can just... do nothing.

```c++
// Inside namespace exercises...
void Val_FDDelta_FDGamma(unsigned int iLocalAccuracy,
         unsigned int iGlobalAccuracy,
         unsigned int iNumberOfPaths,
         mc::scalar sT,
         mc::bvector & ppoInCond,
         mc::scalar eps,
         mc::mc_factory<mc::bvector,mc::bvector> & ParticularFactory,
         mc::payoff<mc::bvector> & ParticularPayoff,
         mc::statistics & ParticularStatisticsVal,
         mc::statistics & ParticularStatisticsDelta,
         mc::statistics & ParticularStatisticsGamma) {

    }
```

Next are the constructors. In these cases most of the constructors just
initialize the member variables directly based on the input arguments of
the constructor. So there's not much to do, I think in this case
writing a dummy implementation is harder than just writing the
actual constructor. 
So I'll do one of them, you can do the others.

```c++
// Inside namespace exercises ...
basket_payoff::basket_payoff(unsigned int indMax): indMax_(indMax) {}
```

Now as for the `operator()` methods; some of them have a `mc::bvector&` output...
as well as an `mc::bvector& bvOut` argument, which seems to imply that
we're supposed to calculate something, put in into `bvOut`, then return `bvOut`.
So we just return `bvOut` for our dummy implementation.

```c++
mc::bvector& basket_payoff::operator()(path_out& poArg, mc::bvector& bvOut) {
    return bvOut;
}
```

The rest of the functions return an `unsigned int` or a `bool`.
I'll leave writing the dummy implementations to you.


# What is MCLib?

> Monte Carlo Project was created for teaching purposes at the Mathematical Intitute, 
> University of Oxford in 2009.
> 
> The code is written by Lajos Gergely Gyurko. 
> Some ideas of the RDE lib coordinated by Terry Lyons in 2005-2006 has been reused.

To get familiar with MCLib, we have three sources of information available;
- The lecture slides, and the lectures themselves.
- The html documentation.
- The source code.

I recommend going through the lecture slides a couple of times to get familiar
with some of the core ideas behind MCLib, in particular

- MCLib is used to make Monte Carlo simulations of stocks, 
and calculate their payoffs.
- The payoffs now can depend on the whole stock price trajectory,
unlike European Call Options where the payoff depends only on the final price.

### Dyadic
`mc::dyadic` is used as "indices", and they represent subdivisions of the 
interval $[0, 1]$ of the form $[k2^{-n}, (k+1)2^{-n}]$.

> dyadic is an implementation of dyadic sub-intervals of $[0,1]$
> 
> The instances of the dyadic type are intervals of the form $[k2^{-n},(k+1)2^{-n}]$. 
> Ordering is defined by $[a,b]<[c,d]$ iff $a < c$ or (a=c and b<d). 
> A version of this class was created in 2005-2006 during the C++ workshops led Terry Lyons.


### Paths

After looking at the documentation, code examples and more,
it seems paths are simply wrappers for 
`std::maps` from `dyadic` to `path_piece`, 
a type parameter which can be `mc::bvector` 
(which is just a boost vector of `mc::scalar`,
where `mc::scalar` is `double`), but it could potentially 
be something different.

Try digging around the lecture notes, the documentation,
and 
[MCLib/type_definitions.hpp](../../Libraries/MCLib/type_definitions.hpp),
and
[MCLib/base_path.hpp](../../Libraries/MCLib/base_path.hpp),
and see if you reach the same conclusions I did, 
as I might be mistaken.

Path pieces come up a lot in MCLib, 
as they are abreviated as `pp`, such as in `PPI`, `PPO`,
`ppInitialValue_`, and so on.


### Payoffs

The payoff class is declared in
[MCLib/base_payoff_statistics.hpp](../../Libraries/MCLib/base_payoff_statistics.hpp).

Like previous times, payoffs are functions that, given a simulation,
return the value earned.

This time, they are function objects (as they are objects which
implement the `operator()` method), the payoffs return
a `mc::bvector`, and they take a whole path into account 
(instead of just the simulated value at time T, like before).

The type is `mc::payoff<path_piece_out>`,
so when the exercise asks for a 
`mc::payoff<mc::bvector>`, 
the path piece type is `mc::bvector`,
so just a boost vector of doubles.

One last thing,
the `SizePayoff` function seems to be the function
that gives the size of the boost vectors returned by
`operator()`.


### Example of Payoffs

[MCLib/Src/particular_payoff_statistics.cpp](../../Libraries/MCLib/Src/particular_payoff_statistics.cpp)
has a few examples of implementing payoff functions,
this can be useful when implementing your own.

In particular, there's one for European call options!

```c++
pmc::european_calls_payoff::
european_calls_payoff(const mc::bvector & bvStrikes, 
		      unsigned int ind)
  : bvStrikes_(bvStrikes),
    ind_(ind)		
{}
```
The constructor is fairly simple, 
it just stores the input arguments into private member variables.

```c++
unsigned int pmc::european_calls_payoff::SizePayoff() const {
  return bvStrikes_.size();
}
```
The SizePayoff, in this case, is based on the `bvStrikes`
argument's size.

```c++	
mc::bvector & pmc::european_calls_payoff::
operator()(path_out & poArg, mc::bvector & bvOut)
{
  const mc::bvector & underlying=poArg.find(mc::dyadic(0,0))->second;
  size_t n=SizePayoff();
  bvOut.resize(n);

  for(size_t i=0; i<n; ++i)
    bvOut[i]=std::max(underlying[ind_]-bvStrikes_[i],0.0);

  return bvOut;
}
```

Finally, the `operator()` has the
`std::max(underlying[ind_]-bvStrikes_[i],0.0);`
formula that we're familiar with at this point;
`underlying[ind_]` somehow is the specific stock whose price
we're interested in, while `bvStrikes_[i]` is the strike price.

### Statistic

`mc::statistic` are declared in [MCLib/base_payoff_statistics.hpp](../../Libraries/MCLib/base_payoff_statistics.hpp),
and some of them are defined in [MCLib/Src/particular_payoff_statistics.cpp](../..Libraries/MCLib/Src/particular_payoff_statistics.cpp).

The key idea is that you get some values and use
`mc::statistics::DumpOnePayoff(value)`
for each value, 
and this will keep track of how many values we've dumped,
and calculate the average and standard deviation for us.


# Any hints for Exercise 2?

In exercise 2, we want to calculate three statistics,
the first one is similar to previous Monte Carlo estimates
we've done, but this time using MCLib,
with `mc_factory` and all that.
Lecture slides for lecture 14 should have some details
on how it can be used.

It also mentions that there's two versions of `GetNewPathOut`.

Now, this can help calculate one of the three statistics you need,
however the other statistics require you to consider
$S^{s+\epsilon}_T$ and $S^{s-\epsilon}_T$.
These essentially are just the same simulations we had before,
but with the initial stock prices changed by epsilon
(`eps` in the arguments).
However, these simulations with different starting stock prices
need to have the same noise as with the first simulation we had.


