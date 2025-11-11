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


SparseVector exercises::operator+(const SparseVector & svArg1, 
			const SparseVector & svArg2)
{
	SparseVector res(svArg1);

	SparseVector::const_iterator sv2Iter = svArg2.begin();
	SparseVector::const_iterator sv2eIter = svArg2.end();
	for( ;sv2Iter != sv2eIter; ++sv2Iter) 
	{
		SparseVector::iterator sv1Iter = res.find(sv2Iter->first);
		
		//checking if entry does not exist
		if(sv1Iter == res.end() && (sv2Iter->second) != 0.0)
			res.insert((*sv2Iter));

		else if(sv1Iter != res.end()) //if entry extist, then update
		{
			sv1Iter->second += sv2Iter->second;
			if(sv1Iter->second == 0.0) //if entry becomes zero, then remove
				res.erase(sv1Iter);
		}
	}
	//return new vector
	return res;
}

SparseVector & exercises::operator-=(SparseVector & svArg1, const SparseVector & svArg2)
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
			svArg1.insert(std::make_pair(sv2Iter->first, -(sv2Iter->second)));
		//alternative code for line 32:
		else if(sv1Iter != svArg1.end()) //if entry extist, then update
		{
			sv1Iter->second -= sv2Iter->second;
			if(sv1Iter->second == 0.0) //if entry becomes zero, then remove
				svArg1.erase(sv1Iter);
		}
	}
	//return reference to first argument
	return svArg1;
}

SparseVector exercises::operator-(const SparseVector & svArg1, const SparseVector & svArg2)
{
	SparseVector res(svArg1);

	SparseVector::const_iterator sv2Iter = svArg2.begin();
	SparseVector::const_iterator sv2eIter = svArg2.end();
	for( ;sv2Iter != sv2eIter; ++sv2Iter) 
	{
		SparseVector::iterator sv1Iter = res.find(sv2Iter->first);
		
		//checking if entry does not exist
		if(sv1Iter == res.end() && (sv2Iter->second) != 0.0)
			res.insert(std::make_pair(sv2Iter->first, -(sv2Iter->second)));

		else if(sv1Iter != res.end()) //if entry extist, then update
		{
			sv1Iter->second -= sv2Iter->second;
			if(sv1Iter->second == 0.0) //if entry becomes zero, then remove
				res.erase(sv1Iter);
		}
	}
	//return new vector
	return res;
}


SparseVector & exercises::operator*=(SparseVector & svArg, const double dArg)
{
	if (dArg == 0.0) // Correctly handles scalar multiplication by zero
	{
		svArg.clear();
		return svArg;
	}

    // Use a range-based for loop to iterate over *existing* elements only
	for (auto& pair : svArg) 
	{
		pair.second *= dArg;
        // Since dArg != 0.0, we don't need to check if the new value is 0.0
	}
    // Note: Erasing if dArg != 0.0 is unnecessary unless the double value suddenly hits 0.0
    // due to floating-point issues, but for this context, it's safer to rely on the
    // assumption that non-zero * non-zero is non-zero.

	return svArg;
}

SparseVector exercises::operator*(const SparseVector & svArg, const double dArg)
{
// Create a copy to perform the operation on
    SparseVector res(svArg); 
    
    // Use the correctly implemented compound operator *=
    res *= dArg; 
    return res;
}

SparseVector exercises::operator*(const double dArg, const SparseVector & svArg)
{
	SparseVector res(svArg);
	if (dArg == 0.0) // Sparse vector can't have any zeros, so if dArg is zero, return empty vector
	{
		res.clear();
		return res;
	}
	for (auto i = 0; i < svArg.size(); ++i) 
	{
		res[i] *= dArg;
	}
	return res;
}
