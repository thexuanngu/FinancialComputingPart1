#ifndef _PRACTICAL07EXERCISES_HPP__
#define _PRACTICAL07EXERCISES_HPP__

#include "MCLib/base_payoff_statistics.hpp"
#include "MCLib/particular_payoff_statistics.hpp"
#include "MCLib/base_factory.hpp"
#include <vector>

namespace exercises
{



/** \class basket_payoff
	\brief basket_payoff is a particular payoff

	basket_payoff implements a non-path dependent option. The payoff
	is the max(Y_t[0],...,Y_T[n-1]), where n=min(indMax,lenght of Y_T)
	This version has a 1dim payoff.
*/
class basket_payoff : 
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	* @param indMax defines the last index taken into account
	*/
  basket_payoff(unsigned int indMax=1);

	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg,
			   mc::bvector & bvOut) override;

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	 */
  unsigned int SizePayoff() const override;

private:
  unsigned int indMax_;//!< defines n
};


/** \class geometric_average_payoff
	\brief geometric_average_payoff is a particular payoff

	geometric_average_payoff implements path dependent option. The payoff
	is the (Y_{t_1}[ind]*...*Y_{t_n}[ind])^{1/n}, 
	This version has a 1dim payoff.
*/
class geometric_average_payoff : 
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	* @param iSamplingAccuracy defines the scale on which the average is sampled
	* @param indY defines the component to be averaged
	*/
  geometric_average_payoff(unsigned int iSamplingAccuracy,
			   unsigned int indY=0);

	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg,
			   mc::bvector & bvOut) override;

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	 */
  unsigned int SizePayoff() const override;

private:
  unsigned int iSamplingAccuracy_;//!< the average is taken over a scale of 2^{ISamplingAccuracy) steps
  unsigned int indY_;//!< the index of the component to be averaged
};




/** \class half_call_half_put
	\brief particular time-dependent payoff, up to mid term it's call, then it's put

	*/
class half_call_half_put : 
  public mc::time_dependent_payoff<mc::bvector>
{
public:

	/** TimeDependentCall constructor
	* @param bvStrikes sets the vector of strikes 
	* @param index sets the index of the underlying in the path_piece vector
	  */
  half_call_half_put(const mc::bvector & bvStrikes,
		     mc::bvector::size_type index=0);

	/** operator()
	 * @param pFactors path argument along which the payoff to be worked out
	 * @param dTimeStep defines time(step)
	 * @param bvValue result is written into
	 * @return reference to bvValue
	  */
  mc::bvector & operator()(path_out & pFactors, 
			   const mc::dyadic & dTimeStep, 
			   mc::bvector & bvValue) override;

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	  */
  unsigned int SizePayoff() const override;

private:
  mc::bvector::size_type m_index;//!< index of the underlying in path_piece for option payoff 
  mc::bvector m_bvStrikes;//!< vector of strikes 
};


/** \class UpRangeOut
	\brief UpRangeOut is a particular KO condition
	
	The uption is knocked out after the stock price has been above
	the upper barrier U for N barrier times. Otherwise, it behaves as standard
	European put option with maturity T and strike K.
*/
class UpRangeOut
{
public:
  UpRangeOut(mc::scalar sUpperBarrier,
	     unsigned int iNumberOfeventsBarrier,
	     unsigned int ind=0);

  bool operator()(const mc::bvector & bvArg);

  void Reset()
  { iNumberOfeventsLeft_=iNumberOfeventsBarrier_;}

private:
  mc::scalar sUpperBarrier_;//!< upper barrier
  unsigned int ind_;//!< index of component triggering the KO
  unsigned int iNumberOfeventsBarrier_;//!< maximum number barrier events until KO
  unsigned int iNumberOfeventsLeft_;//!< remaining number of barrier events until KO
	 
};

  /** Val_FDDelta_FDGamma Monte-Carlo and finite difference based estimate of option value, its delta and its gamma
  * @param iLocalAccuracy defines the scale of the numerical method
  * @param iGlobalAccuracy defines the scale of the solution path
  * @param iNumberOfPaths number of paths to be simulated
  * @param sT time horizon - scaling parameter
  * @param ppoInCond initial condition of solution
  * @param eps tweak size (or bump size)
  * @param ParticularFactory defines a set of rules (input noise generation, numerical SDE etc.)
  * @param ParticularPayoff defines the payoff function 
  * @param ParticularStatisticsVal statistics object to dump the payoff values into
  * @param ParticularStatisticsDelta statistics object to dump the finite diff that estimates delta into
  * @param ParticularStatisticsGamma statistics object to dump the finite diff that estimates gamma into
  */
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
			 mc::statistics & ParticularStatisticsGamma);


}

#endif //_PRACTICAL07EXERCISES_HPP__
