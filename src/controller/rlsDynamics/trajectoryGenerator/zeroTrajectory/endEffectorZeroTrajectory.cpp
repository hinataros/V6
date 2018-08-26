/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::endEffectorZeroTrajectory(double &t)
{
  if(debug) DEBUG;

  int size = cal_XDes.size();

  cal_XDes = sequence[endEffectorTrajectoryNum].cal_XpreDes + cal_X0;
  cal_VxiDes = VectorXd::Zero(size);
  cal_dVxiDes = VectorXd::Zero(size);
}
