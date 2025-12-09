#include "Practical07/Practical07Exercises.hpp"

namespace exercises {
    
    basket_payoff::basket_payoff(unsigned int indMax)
        : indMax_(indMax) {}

        mc::bvector & basket_payoff::operator()(path_out & poArg, mc::bvector & bvOut) {
            // Initialize the output vector
            bvOut.resize(1); bvOut[0] = 0.0;

            // Get the final stock values
            const mc::bvector & finalValues = poArg.find(mc::dyadic()) -> second;

            // Find the maximum value
            for (unsigned int i = 0; i < indMax_ && i < finalValues.size(); ++i) {
                if (finalValues[i] > bvOut[0]) {
                    bvOut[0] = std::max(finalValues[i], bvOut[0]);
                }
            }
            return bvOut;
            }

    unsigned int basket_payoff::SizePayoff() const {
        return 1;
    }

    // 
    // Geometric Average Payoff
    //
    geometric_average_payoff::geometric_average_payoff(unsigned int iSamplingAccuracy, 
        unsigned int indY) : iSamplingAccuracy_(iSamplingAccuracy), indY_(indY) {}
        // iSamplingAccuracy_ defines the scale on which the average is sampled
        // indY_ defines the component to be averaged

    mc::bvector & geometric_average_payoff::operator()(
        path_out & poArg, mc::bvector & bvOut) {
        // Initialize the output vector
        bvOut.resize(1); bvOut[0] = 1.0; // Start with multiplicative identity
        const int m = 1 << iSamplingAccuracy_; // Number of samples: 2^{iSamplingAccuracy_}

        // Set up our interval for iteration
        mc::dyadic itv(0, iSamplingAccuracy_); // Start at [0, 2^{-iSamplingAccuracy_})

        // Loop through time, capture the product
        for (int idx = 0; idx < m; idx++, itv++) {
            // Collect the product
            bvOut[0] *= poArg.find(itv)->second[indY_]; // Remember that this is a pair, and we need a specific element
        }

        // Take the mth root
        bvOut[0] = std::pow(bvOut[0], 1.0 / m); // Make sure it's a float!

        return bvOut;
    }

    unsigned int geometric_average_payoff::SizePayoff() const {
        return 1;
    }

    // Particular Time-Dependent Payoff -> Like a call in the beginning, then a put in the end -> Care about value in a specific interval
    half_call_half_put::half_call_half_put(const mc::bvector & bvStrikes, 
        mc::bvector::size_type index) : m_bvStrikes(bvStrikes), m_index(index) {}


    mc::bvector & half_call_half_put::operator()(path_out & pFactors, 
        const mc::dyadic & dTimeStep, 
        mc::bvector & bvValue) {
        // Initialize the output vector
        bvValue.resize(SizePayoff()); bvValue.clear();

        // Decide if we have a call or a put
        bool call_or_put = dTimeStep < mc::dyadic(1,1);
        call_or_put = dTimeStep.Position() < (1 << (dTimeStep.Accuracy() - 1));

        // Find the stock values
        const mc::bvector & stockValues = pFactors.find(dTimeStep)->second;

        // Loop through the strikes
        for (unsigned int i = 0; i < m_bvStrikes.size(); ++i) {

            // Calculate the payoff
            if (call_or_put) {
                bvValue[i] = std::max(m_bvStrikes[i] - stockValues[m_index], 0.0);
            } else {
                bvValue[i] = std::max(stockValues[m_index] - m_bvStrikes[i], 0.0);
            }
        }

        // Get the values

        return bvValue;
        }

    unsigned int half_call_half_put::SizePayoff() const {
        return m_bvStrikes.size();
    }

    UpRangeOut::UpRangeOut(mc::scalar sUpperBarrier,
         unsigned int iNumberOfeventsBarrier,
         unsigned int ind)
        : sUpperBarrier_(sUpperBarrier),
          ind_(ind),
          iNumberOfeventsBarrier_(iNumberOfeventsBarrier),
          iNumberOfeventsLeft_(iNumberOfeventsBarrier) {}

    bool UpRangeOut::operator()(const mc::bvector & bvArg) {
        // If only one barrier is left
        // Then it all depends on if we've crossed or not
        if (iNumberOfeventsLeft_ == 1) {
            return bvArg[ind_] > sUpperBarrier_;
        }


            if (bvArg[ind_] > sUpperBarrier_) { iNumberOfeventsLeft_--;} 
            return false; // Still alive
        }

        // Otherwise, remove a barrier if we've above...
        // but always return False


    void Val_FDDelta_FDGamma(unsigned int iLocalAccuracy,
             unsigned int iGlobalAccuracy,
             unsigned int iNumberOfPaths,
             mc::scalar sT,
             mc::bvector & ppoInCond, // Initial conditions
             mc::scalar eps,
             mc::mc_factory<mc::bvector,mc::bvector> & ParticularFactory,
             mc::payoff<mc::bvector> & ParticularPayoff,
             mc::statistics & ParticularStatisticsVal,
             mc::statistics & ParticularStatisticsDelta,
             mc::statistics & ParticularStatisticsGamma) {
                // We are going to use mc:statistics

                // Initial Conditions
                mc::bvector ppoInCond_minus(ppoInCond);
                mc::bvector ppoInCond_plus(ppoInCond);
                for (int idx = 0; idx < ppoInCond.size(); ++idx) {
                    ppoInCond_minus[idx] -= eps;
                    ppoInCond_plus[idx] += eps;
                }

                // Vectors containing the payoffs
                mc::bvector values_center(ParticularPayoff.SizePayoff());
                mc::bvector values_minus(ParticularPayoff.SizePayoff());
                mc::bvector values_plus(ParticularPayoff.SizePayoff());
                mc::bvector delta(ParticularPayoff.SizePayoff());
                mc::bvector gamma(ParticularPayoff.SizePayoff());

                // Simulate Paths
                for (int step = 0; step < iNumberOfPaths; ++step) {
                    // Generate Noise
                    auto noise_ptr = ParticularFactory.GetNewPathInPtr(iLocalAccuracy, sT); // sT = Scalar Time

                    // Generate Paths from that Noise
                    auto path_center = ParticularFactory.GetNewPathOut(noise_ptr, iLocalAccuracy, iGlobalAccuracy, ppoInCond, sT);
                    auto path_minus = ParticularFactory.GetNewPathOut(noise_ptr, iLocalAccuracy, iGlobalAccuracy, ppoInCond_minus, sT);
                    auto path_plus = ParticularFactory.GetNewPathOut(noise_ptr, iLocalAccuracy, iGlobalAccuracy, ppoInCond_plus, sT);

                    // Get Payoff Values
                    ParticularPayoff(path_center, values_center);
                    ParticularPayoff(path_minus, values_minus);
                    ParticularPayoff(path_plus, values_plus);

                    // Calculate delta and gamma
                    delta = (values_plus - values_minus) / (2.0 * eps);
                    gamma = (values_plus - 2 * values_center + values_minus) / (eps * eps);
                    
                    // Dump Statistics
                    ParticularStatisticsVal.DumpOnePayoff(values_center);
                    ParticularStatisticsDelta.DumpOnePayoff(delta);
                    ParticularStatisticsGamma.DumpOnePayoff(gamma);
                }
             }
}