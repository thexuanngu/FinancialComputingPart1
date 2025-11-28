#include "Practical06/Practical06Exercises.hpp"
#include <algorithm>
#include <numeric>

using namespace exercises;
using namespace std;


//***********************************************************************
// CallPayoff
//***********************************************************************
class ICallPayoff : public IFunction
{
public:
	ICallPayoff(double dK, BVector::size_type index) : m_dK(dK), m_index(index) {}
	double operator()(const BVector & bvArg) const
	{
		return max(0.0,bvArg[m_index]-m_dK);
	}

private:
	double m_dK;
	BVector::size_type m_index;
};

Function exercises::CallPayoff(double dK,BVector::size_type index)
{
	return Function(make_shared<ICallPayoff>(dK,index));
}