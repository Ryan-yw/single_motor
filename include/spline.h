#ifndef TOOLS_H
#define TOOLS_H
#include "aris.hpp"

namespace spline{
/**
 * @brief the quintic interpolation of one dimension, return position at t
 * @param q0 start position
 * @param qf end position
 * @param dq0 start velocity
 * @param dqf end velocity
 * @param ddq0 start accelaration
 * @param ddqf end accelaration
 * @param t0 start time
 * @param t output time
 * @param tf end time
 * @param result output position at time t
 */
double quintic(const double q0, const double qf, const double dq0, const double dqf, const double ddq0, const double ddqf, const double t0, const double t, const double tf, double & result);
std::vector<double>& quintic(const std::vector<double> q0, const std::vector<double> dq0, const std::vector<double> ddq0,
                             const std::vector<double> qf, const std::vector<double> dqf, const std::vector<double> ddqf,
                             const double t0, const double tf, double t, std::vector<double> &result);


}
#endif // TOOLS_H
