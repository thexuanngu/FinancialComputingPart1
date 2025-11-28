#ifndef _DEFINITIONS_H__
#define _DEFINITIONS_H__

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <memory>

namespace exercises
{

  class IFunction; //forward declaration of IFunction
  class Function;  //forward declaration of Function

  typedef std::shared_ptr<const IFunction> IFunPtr; //smart pointer to IFunction
  typedef boost::numeric::ublas::vector<double> BVector; //boost vector of doubles

}




#endif //_DEFINITIONS_H__
