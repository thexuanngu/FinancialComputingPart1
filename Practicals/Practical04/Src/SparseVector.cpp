#include "Practical04/SparseVector.hpp"

using namespace exercises;
using namespace std;

std::ostream & exercises::operator<<(std::ostream & os, const SparseVector & svArg)
{
	os << "{"; 
	SparseVector::const_iterator svIter=svArg.begin();
	SparseVector::const_iterator sveIter=svArg.end();
	for(;svIter!=sveIter; ++svIter) 
		os << "[" << svIter->first << "] " << svIter->second << "  ";

	os<< "}";

	return os;
}

SparseVector & exercises::operator+=(SparseVector & svArg1, 
					const SparseVector & svArg2)
{
	SparseVector::const_iterator sv2Iter = svArg2.begin();
	SparseVector::const_iterator sv2eIter = svArg2.end();
	for( ;sv2Iter != sv2eIter; ++sv2Iter) 
	{
		SparseVector::iterator sv1Iter = svArg1.find(sv2Iter->first);
		//alternative code for line 26:
		//SparseVector::iterator sv1Iter=svArg1.find((*sv2Iter).first);
		
		//checking if entry does not exist
		if(sv1Iter == svArg1.end() && (sv2Iter->second) != 0.0)
			svArg1.insert(*sv2Iter);
		//alternative code for line 32:
		//svArg1.insert(std::make_pair(sv2Iter->first,sv2Iter->second));
		else if(sv1Iter != svArg1.end()) //if entry extist, then update
		{
			sv1Iter->second += sv2Iter->second;
			if(sv1Iter->second == 0.0) //if entry becomes zero, then remove
				svArg1.erase(sv1Iter);
		}
	}
	//return reference to first argument
	return svArg1;
}

/*

SparseVector exercises::operator+(const SparseVector & svArg1, 
			const SparseVector & svArg2)
{
	SparseVector res;
	//...
	return res;
}

SparseVector & exercises::operator-=(SparseVector & svArg1, const SparseVector & svArg2)
{
	//...
	return svArg1;
}

SparseVector exercises::operator-(const SparseVector & svArg1, const SparseVector & svArg2)
{
	SparseVector res;
	//...
	return res;
}


SparseVector & exercises::operator*=(SparseVector & svArg, const double dArg)
{
	//...
	return svArg;
}

SparseVector exercises::operator*(const SparseVector & svArg, const double dArg)
{
	SparseVector res;
	//...
	return res;
}

SparseVector exercises::operator*(const double dArg, const SparseVector & svArg)
{
	SparseVector res;
	//...
	return res;
}

*/
