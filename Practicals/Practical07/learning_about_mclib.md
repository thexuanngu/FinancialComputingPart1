# Learning about MCLib

There's a few different ways to learn about MCLib;
- The lectures and lecture notes.
- The HTML documentation, available in the [course's page](https://courses.maths.ox.ac.uk/course/view.php?id=5974).
- Digging through its header files.
- Digging through its C++ files.
- Digging through the lecture's C++ files.

We'll use a hybrid approach towards figuring things out.

In practice, being able to learn how to use a library on your own is
a very useful skill, since there's always new libraries,
and each company might have their own custom libraries.
In particular, company custom libraries are more challenging as
you do not have access to resources like the internet,
StackOverflow, or LLMs to help you out; on the other hand
you may have access to coworkers who have experience with the library.

# First steps

## What is this library about?

This is the first thing we want to figure out. 
We start by looking at the documentation

> Monte Carlo Project was created for teaching purposes at the Mathematical Intitute,
> University of Oxford in 2009.
>
> The code is written by Lajos Gergely Gyurko.
> Some ideas of the RDE lib coordinated by Terry Lyons in 2005-2006 has been reused.

Well, now we know the MC in MCLib stands for Monte Carlo.
So we'll assume it's going to be used for making
Monte Carlo simulations.

The lecture notes gives us a more in-depth explanation.

> The main goal is to implement **a tool for pricing
> financial derivatives** based on Monte Carlo type simulations.
> In particular, we would like to use the library for
> - **Simulating general input noise** [...]
> - **solving/approximating solutions to stochastic
> differential equations** driven by some input noise using general
> **global strategies** [...] in combination with **local techniques** [...]
> - evaluating general **payoff** functions [...]
> - computing general **statistics** [...]

So it's going to be a bit like our first implementations of
Monte Carlo simulations;
- We're going to generate some noise.
- We're going to simulate a stock price's path.
- We're going to find the payoff from this data (wether
that's just the end price or something related to the whole path).
- We're going to calculate some statistics from these payoffs.

In theory though, the library would be useful to combine
many different methods to generate noise,
methods to simulate the stock, 
methods to calculate payoffs, etc.


## What are the key pieces?

We now try to find what's the core of it, 
and what's the additional stuff available in the library.
Going to the official documentation we find the 
*Namespaces > Namespace List* which is a bit like a table of contents.

We notice there's `mc` and `pmc`; 
the first of which seems to have the core classes like `payoff`, 
whereas the second seems to have specific implementations
like `european_calls_payoff`.

So before we do the exercises, we might want to have a look at
`mc` and familiarize ourselves a bit with it.
And while doing the exercises, we might want to have a look at
`pmc` for examples similar to what we'll be aiming to do.

Within `mc`, some classes seem to be more important than others,
so let's focus on those.

| Class                   | Short Description                                                         |
|-------------------------|---------------------------------------------------------------------------|
| `dyadic`                | Dyadic is an implementation of dyadic sub-intervals of [0,1]              |
| `mc_factory`            | Mc_factory is the base class for setting up mc path generators            |
| `path`                  | Path is a class used to model random trajectories                         |
| `payoff`                | Payoff is the base class for particular payoffs                           |
| `regression` | Base class for least-squares regression based methods 
| `statistics`            | Statistics is the base class for particular statistics                    |
| `time_dependent_payoff` | Abstract base class for time dependent payoffs, templated with path_piece |

The core of it seems to be `path`, 
which model the stock prices' paths, 
as well as the random input noises.
- `mc_factory` is used to create these paths.
- `pyoff` and `time_dependent_payoff` use these.
- `dyadic` intervals are used in `path`.


# Dyadic intervals

Looking at the documentation, 

> dyadic is an implementation of dyadic sub-intervals of $[0,1]$
>
> The instances of the dyadic type are intervals of the form $[k2^{-n},(k+1)2^{-n}]$.
> Ordering is defined by $[a,b]<[c,d]$ iff $a < c$ or (a=c and b<d).
> A version of this class was created in 2005-2006 during the C++ workshops led Terry Lyons.

Looking at 
[dyadic_interval.hpp](../../Libraries/MCLib/dyadic_interval.hpp),

```c++
// Inside class dyadic
private:
	unsigned int k; //!< coefficient 
	unsigned int n; //!< exponent*(-1)
```
So each dyadic interval really is just the 
$(k,n)$ pair of integers internally.

These can be recovered with 
```c++
inline unsigned int Accuracy() const {return n;}
inline unsigned int Position() const {return k;}
```

The constructor just sets the $(k, n)$ pair,
```c++
/** Constructor.
* Constructs the interval [k2^{-n},(k+1)2^{-n)].
* @param kArg coefficient
* @param nArg exponent*(-1)
*/
dyadic(unsigned int kArg, unsigned int nArg): 
    k(std::min<int>(kArg,(1<<nArg)-1)), 
    n(nArg) {}
```

So for example
`dyadic(0,0)` is the $[0,1]$ interval, and
`dyadic(1,1)` is the $[\frac{1}{2}, 1]$ interval.

Of interest are a few operators that are available.
- `+` and `++` shift the interval by changing the $k$ value.
- `<` gives us an order on the dyadic intervals, 
the one described in the description at the start of this class.


# Paths

We once again look at the documentation...

> path is a class used to model random trajectories
> 
> From outside the class looks as a read-only container of data of type `path_piece`. 
> `path_piece` is the type of input noise pieces, 
> which could be increments, increments and areas, 
> signature upto certain level, etc. 
> The container is of type map, 
> assigning `path_piece` data to `dyadic` intervals. 
> The actual `path_piece` data generation is done through the member 
> of type `path_generator`. 
> Accuracy defines the fineness of the time scale for which `path_piece`s 
> can be returned. 
> Note that accuracy might be `INT_MAX` 
> (see Levy construction based path generation). 

Let's not worry too much about constructing paths
as we'll be doing that with factories.
The key is learning how we can use paths.

It seems to behave a bit like a `std::map<dyadic, path_piece>`,
and as such we might hope to find a `find` method,
and we do!
```c++
const_iterator find(const dyadic & dyArg)
```

This does bring us to a rather important issue...
What are all these types floating around?

## Types...

We begin with
[type_definitions.hpp](../../Libraries/MCLib/type_definitions.hpp).

```c++
typedef double scalar;//!<scalar type
typedef boost::numeric::ublas::vector<scalar> bvector;//!<boost vector of scalars
```

Which means that `mc::scalar` is just a `double` in disguise,
and `mc::bvector` is a boost vector of scalars/doubles.

> Aside: In C++ it is possible to have template parameters be
> integers instead of types. 
> These allow for example to create types like
> "A vector of 3 doubles" instead of "A vector of doubles".
> These types could have been used in MCLib to avoid errors
> where we're creating vectors of the wrong size and trying
> to access data outside of them.

Next are a few types that depend on some type `path_piece`, 
which often ends up being `mc::bvector`,
but which a priori could be a different type.

```c++
template<class path_piece>
struct path_piece_types
{
    typedef typename std::map<mc::dyadic,path_piece> path_map;//!<path container member
    typedef typename path_map::iterator iterator;//!<iterator of path_map
    typedef typename path_map::const_iterator const_iterator;//!<const iterator of path_map
    
    typedef typename std::map<mc::dyadic,path_piece,dyadicLessByRightEnd> path_map_by_right_end;//!<path container member
};
```

So `path_map` is a `std::map<mc::dyadic,path_piece>`,
and `const_iterator` is its iterator type.

Going back to [base_path.hpp](../../Libraries/MCLib/base_path.hpp),
we see that we have 

```c++
template<class path_piece, class PM=typename mc::path_piece_types<path_piece>::path_map >
class path
{
public:
	typedef PM path_map;
	typedef typename path_map::iterator iterator;//!<iterator of path_map
	typedef typename path_map::const_iterator const_iterator;//!<const iterator of path_map
	typedef sptr::shared_ptr<pmc::path_generator<path_piece,path_map> > path_generator_ptr;//!<pointer to path generator
    // ...
```

So given a `path_piece`, 
it lets `PM` be its 
`mc::path_piece_types<path_piece>::path_map`,
then renames `PM` to `path_map`, 
and similarly declares `const_iterator`.

## Internal data of a Path

Let's look at a base path's private data,
```c++
// Inside path
private://data members
    scalar sT_;//!< time horizon
    path_piece ppInitialValue_; //<! initial state of the path
    path_map pmContainer_;//!< contains the already generated PP's
    path_generator_ptr pgpGenerator_;//!< ptr to generator, [const PP & op()(const dyadic &, path_map &, scalar) const] member assumed
```

So it does contain a `path_map`! 
It also keeps track of $T$, the time horizon,
so that the path represents $[0,T]$ instead of just $[0, 1]$.
There's also the initial value, 
as well as a (pointer to a) path generator.

If we look at the internals of how `find` is implemented,
it calls this generator instead of just wrapping around
the `path_map`'s `find` method; 
but that's not something we need to concern ourselves with,
for our purposes it's good enough to think of a
`path` as a wrapper of our map from dyadic intervals
to "path-pieces which are basically bvectors".

```c++
const_iterator find(const dyadic & dyArg)
    {
        return pgpGenerator_->operator()(dyArg,pmContainer_,sT_,ppInitialValue_);
    }
```

# Payoffs

We next have a brief look at
[base_payoff_statistics.hpp](../../Libraries/MCLib/base_payoff_statistics.hpp)

We see then that, as usual, a Payoff is a function, 
in this case a function object.
```c++
template<class path_piece_out, /* ... */ >
class payoff
{
public:
    typedef typename mc::path<path_piece_out, PM> path_out;//!<solution path
    
    virtual ~payoff(){}
    virtual mc::bvector & operator()(path_out & poArg, mc::bvector & bvOut)=0;
    virtual unsigned int SizePayoff() const=0;
};
```

As a function, it now takes `poArg`, a path;
as well as `bvOut`, a `mc::bvector`, which is also its return type.
So it's a function which "takes the location of its output as an input,
and writes the output there, and also returns the output".

> *Why have functions that take the place to write output
> as an input instead of returning it as output?*
> This allows us to have great control of exactly where memory is
> being allocated, and is particularly useful for when
> we are working with large objects which we don't want to
> create duplicates of.
> 
> *Why return a value if it's already been updated?*
> This allows for expressivity in certain cases.
> A similar example is a class whose methods return always
> returns the object itself, this allows for chaining methods;
> ```c++
> Point(0.0,0.0).forward(1.0).rotate(1.22322).scale(4.0);
>```

## Time dependent payoffs

Time dependent payoffs are quite similar,
but instead of just depending on the path,
they also depend on a specific time.

```c++
template<typename path_piece_out, /* ... */>
class time_dependent_payoff
{
public:
    typedef mc::path<path_piece_out,PM> path_out;//!<solution path
    
    virtual ~time_dependent_payoff(){}
    virtual mc::bvector & operator()(
        path_out & pFactors, const mc::dyadic & dTimeStep, mc::bvector & bvValue)=0;
    virtual unsigned int SizePayoff() const=0;
};
```

Here the path is `pFactors`, the output vector to write to is `bvValue`, and now there is a dyadic `dTimeStep` giving the specific time the payoff is dependent on.

# Statistic

Statistics are quite interesting, and still in
[base_payoff_statistics.hpp](../../Libraries/MCLib/base_payoff_statistics.hpp)

```c++
class statistics
{
public:
    typedef std::vector<mc::bvector> result_type;//!<result type
    virtual ~statistics(){}
    virtual void DumpOnePayoff(mc::bvector & bvArg)=0;
    virtual std::vector<mc::bvector> GetStatistics()=0;
};
```
The key is that they have a `DumpOnePayoff` method
where we put a `mc::bvector`,
we do this one by one,
and then whenever we want the statistic we just
call `GetStatistics`.

An example of a `statistic` object might keep track of
the sum of all values as well as the number of values,
and then use this to calculate the `mean` at
any point.
So the `DumpOnePayoff` would just increase the
sum of all values and the total number of values.

An example is in 
[particular_payoff_statistics](../../Libraries/MCLib/Src/particular_payoff_statistics.cpp),
`pmc::mean_variance_statistics`;
how would you implement this?


# MC Factory

We have a look at 
[base_factory.hpp](../../Libraries/MCLib/base_factory.hpp)

```c++
template<class PPI,class PPO, /* ... */>
class mc_factory
{
public:
    // typedefs...
    virtual ~mc_factory(){}
    
    virtual path_in GetNewPathIn(
        unsigned int iAccuracyLimit, mc::scalar sT)=0;
    
    virtual path_in_ptr GetNewPathInPtr(
        unsigned int iAccuracyLimit, mc::scalar sT)=0;
    
    virtual path_out GetNewPathOut(
        unsigned int iAccuracyLimit, unsigned int iGlobalAccuracy,
        path_piece_out ppoArg, mc::scalar sT)=0;
    
    virtual path_out GetNewPathOut(
        path_in_ptr pipArg,
        unsigned int iAccuracyLimit, unsigned int iGlobalAccuracy,
        path_piece_out ppoArg, mc::scalar sT)=0;
};
```

Digging through the documentation, 
- input paths are the noise paths.
- output paths are the solution paths, the simulated stock prices.

We can generate these through
- `GetNewPathIn` and `GetNewPathInPtr` 
for generating input paths (and get a pointer out of that or not).
- `GetNewPathOut` to generate solution paths,
note that there's two methods with the same name,
one with an input path as input, 
the other without.


# Regression

The definitions for the regression class are in [base_regression.hpp](../../Libraries/MCLib/base_regression.hpp),
and its implementation is in 
[base_regression.inl](../../Libraries/MCLib/Inl/base_regression.inl).

You'll note from the implementation that this is simply a class containing the `Regression` and `Projection` methods we implemented in Practical05, 
to construct classes similar to the `EuropeanOptionPricer` we constructed in Practical05.

In the case of `EuropeanOptionPricer` we only needed to do regression and progression once, as the price of the option only depended on the final value of the stock, however in more complex examples we might need to use regression+progression multimple times; an example is found in Lecture15's Bermudan Option Pricer, whose implementation is in [particular_regression.inl](../../Libraries/MCLib/Inl/particular_regressions.inl).

```c++
template<typename PPI, typename F>
pmc::bermudan_option_pricer<PPI,F>
::bermudan_option_pricer(const std::vector<path_piece_out> & factorsAt0,
    unsigned int iNumericalSDEAccuracy,
    unsigned int iBermudanScaleAccuracy,
    mc::scalar sT,
    mc::scalar sR,
    factory & ParticularFactory,
    time_dependent_payoff & ParticularTimedependentPayoff,
    const fvector & testFunctions)
    : m_TestFunctions(testFunctions)
    {
    typename std::vector<path_piece_out>::size_type n(factorsAt0.size());

    //simulating trajectories and discounted terminal value
    std::vector<path_out> trajectories;
    trajectories.reserve(n);
    std::vector<mc::bvector> yVals(n);
    mc::dyadic dyTime((1<<iBermudanScaleAccuracy)-1,iBermudanScaleAccuracy);//[(2^M-1)*2^(-M),1]
    for(unsigned int i=0; i<n; ++i){
        //path_out pathTemp=ParticularFactory.GetNewPathOut(iNumericalSDEAccuracy,iBermudanScaleAccuracy,factorsAt0[i],sT);
        trajectories.push_back(ParticularFactory.GetNewPathOut(
            iNumericalSDEAccuracy,
            iBermudanScaleAccuracy,
            factorsAt0[i],
            sT
        ));
        ParticularTimedependentPayoff(trajectories.back(),dyTime,yVals[i]) *= 
        std::exp(-sR*sT);
    }
    //backward induction
    std::vector<path_piece_out> factorsAtT(n);
    mc::bvector tempExercise(ParticularTimedependentPayoff.SizePayoff());
    mc::bvector tempContinuation(ParticularTimedependentPayoff.SizePayoff());

    auto maxOp =
    [](mc::scalar x, mc::scalar y){return std::max<mc::scalar>(x,y);};

    --dyTime;
    for(int j=0; j < (1<<iBermudanScaleAccuracy)-1 ; ++j, --dyTime ){
        // accessing factor values at time dyTime
        for(unsigned int i=0; i<n; ++i)
            factorsAtT[i]=trajectories[i].find(dyTime)->second;

        // regression for continuation value
        m_Coefficients=this->Regression(yVals,factorsAtT,m_TestFunctions);

        // dynamic programming principle for value
        // working out new values comparing continuation and exercise values
        for(unsigned int i=0; i<n; ++i){
            // continuation value
            this->Projection(factorsAtT[i],m_TestFunctions,m_Coefficients,tempContinuation);
            // exercise value
            mc::scalar sTTemp=dyTime.GetLength()*mc::scalar(dyTime.Position()+1)*sT;

            ParticularTimedependentPayoff(trajectories[i],dyTime,tempExercise) *= 
            std::exp(-sR*sTTemp);
            //new values
            std::transform(tempExercise.begin(),tempExercise.end(),
            tempContinuation.begin(),yVals[i].begin(), maxOp);
        }
    }
    // last step - regression at time 0 (no payoff assumed at initial time)
    m_Coefficients=this->Regression(yVals,factorsAt0,m_TestFunctions);
}

template<typename PPI, typename F>
mc::bvector & pmc::bermudan_option_pricer<PPI,F>::operator()(
    const path_piece_out & factorAt0, mc::bvector & bvOut)
{
    return this->Projection(factorAt0,m_TestFunctions,m_Coefficients,bvOut);
}
```

I'll note first that, while finding the final 
regression coefficients is significantly more challenging, 
once we have those regression coefficients implementing 
`pmc::bermudan_option_pricer<PPI,F>::operator()`
is as simple as it was for the european option pricer;
we just need to use `Projection` once.

For finding those coefficients, 
the first step is simulating trajectories,
done using `ParticularFactory.GetNewPathOut`,
and calculating their payoff with
`ParticularTimedependentPayoff`.

Then to calculate the final regression coefficients,
we need to use `Regression` and `Projection` several times, 
and since the output of `Projection` are used in the
next `Regression`, 
the `yVals` variable is used to keep track of the 
estimates, while `m_Coefficients` is used
to keep track of the regression coefficients.
