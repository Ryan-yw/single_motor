#include <algorithm>
#include <array>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <iostream>
#include <stdio.h>

#include "spline.h"

namespace spline
{


double quintic(const double q0, const double qf, const double dq0, const double dqf, const double ddq0, const double ddqf, const double t0, const double t, const double tf, double & result){
    double tf_ = tf - t0;
    double a0 = q0;
    double a1 = dq0;
    double a2 = 0.5 * ddq0;
    double a3 = (20.0 * qf-20.0 * q0 - (8.0 * dqf + 12.0 * dq0) * tf_ - (3.0 * ddq0 - ddqf) * std::pow(tf_,2)) / (2.0 * std::pow(tf_,3));
    double a4 = (30.0 * q0 - 30.0 * qf + (14.0 * dqf + 16.0 * dq0) * tf_ + (3.0 * ddq0 - 2.0 * ddqf) * std::pow(tf_,2))/(2.0 * std::pow(tf_,4));
    double a5 = (12.0 * qf - 12.0 * q0- (6.0 * dqf + 6.0 * dq0) * tf_ - (ddq0 - ddqf) * std::pow(tf_,2))/(2.0 * std::pow(tf_,5));

    result = a0 + a1 * (t - t0) + a2 * pow((t - t0),2) + a3 * pow((t - t0),3) + a4 * pow((t - t0),4) + a5 * pow((t - t0),5);
    return result;
}

std::vector<double>& quintic(const std::vector<double> q0, const std::vector<double> dq0, const std::vector<double> ddq0,
                             const std::vector<double> qf, const std::vector<double> dqf, const std::vector<double> ddqf,
                             const double t0, const double tf, double t, std::vector<double> &result)
{
    for(int i = 0; i < q0.size() ;++i)
    {
        quintic(q0[i], qf[i], dq0[i],dqf[i],ddq0[i], ddqf[i],t0,t,tf,result[i]);
    }
    return result;
}






}

