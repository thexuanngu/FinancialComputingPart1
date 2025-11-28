#include "Practical06/Practical06Exercises.hpp"
#include <algorithm>
#include <numeric>

namespace exercises {

    class Anonymous : public IFunction {
    public:
    Anonymous(std::function<double(const BVector&)> f) : the_function(f) {}

    double operator()(const BVector & bvArg) const override {
        return the_function(bvArg);
    }

    private: 
    std::function<double(const BVector&)> the_function;
 };

  Function make_function(std::function<double(const BVector&)> f) {
    return Function(std::make_shared<Anonymous>(f));
 }

    class IPutPayoff : public IFunction {
public:
	IPutPayoff(double dK, BVector::size_type index) : m_dK(dK), m_index(index) {}
	double operator()(const BVector & bvArg) const
	{
		return std::max(0.0, m_dK - bvArg[m_index]);
	}

private:
	double m_dK;
	BVector::size_type m_index;
};

    Function PutPayoff(double dK,BVector::size_type index) {
    // return Function(std::make_shared<IPutPayoff>(dK,index));
    // Capture dK and index by value to avoid dangling references when lambda escapes
    return make_function([dK, index](const BVector& bvArg) -> double {
        return std::max(0.0, dK - bvArg[index]);
    });
 }

    Function SpreadOption(double dK1, double dW1, double dK2, double dW2, BVector::size_type index) {
	 return dW1 * CallPayoff(dK1, index) + dW2 * CallPayoff(dK2, index);
 }

    Function StraddleOption(double dK1, double dW1, double dK2, double dW2, BVector::size_type index) {
	return dW1 * CallPayoff(dK1, index) + dW2 * PutPayoff(dK2, index);
 }

    Function BasketPayoff() {
	 return make_function([](const BVector& bvArg) -> double {
        double result = 0.0;
        for (double val : bvArg) {
            result = std::max(result, val);
            }
        return result;
    });
 }

    Function AveragePayoff() {
     return Function(std::make_shared<Anonymous>([](const BVector& bvArg) -> double { 
        return std::accumulate(bvArg.begin(), bvArg.end(), 0.0) / bvArg.size(); }));
 }

    Function SumOfSquares() {
	 return make_function([](const BVector& bvArg) -> double {
        double result = 0.0;
        for (double val : bvArg) {
            result += val * val;
            }
        return result;
    });
 }

   Function InnerProduct(const BVector & bvBase) {
    // Capture bvBase by value so the returned function owns its copy
    return make_function([bvBase](const BVector& bvArg) -> double {
        double result = 0.0;
        for (std::size_t idx = 0; idx < bvArg.size(); ++idx) {
            result += bvArg[idx] * bvBase[idx];
            }
        return result;
    });
    }
}