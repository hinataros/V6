/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::desiredControlNodeAccelerationZeroGenerator(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  cal_XDes.segment(6*controlNode, 6) = cal_X.segment(6*controlNode, 6);
  cal_VxiDes.segment(6*controlNode, 6) = Vector6d::Zero();
  cal_dVxiDes.segment(6*controlNode, 6) = Vector6d::Zero();
}
