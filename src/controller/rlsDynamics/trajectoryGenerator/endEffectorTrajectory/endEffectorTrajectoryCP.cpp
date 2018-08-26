/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::endEffectorTrajectoryCP(double &t)
{
  if(debug) DEBUG;

  int size = cal_XDes.size();

  double tw0 = sequence[endEffectorTrajectoryNum].tw0;
  double twf = sequence[endEffectorTrajectoryNum].twf;
  VectorXd initialDes = sequence[endEffectorTrajectoryNum].cal_XpreDes;
  VectorXd finalDes = sequence[endEffectorTrajectoryNum].cal_Xf;

  for(int i=0; i<size; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));
    cal_XDes(i) = des(0) + cal_X0(i);
    cal_VxiDes(i) = des(1);
    cal_dVxiDes(i) = des(2);
  }
}
