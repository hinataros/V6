/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::controlNodeTrajectoryCP(double &t)
{
  if(debug) DEBUG;

    controlNodeTrajectory_ptr = map_endEffectorTrajectory[controlNodeTrajectoryName[i]];

    (this->*controlNodeTrajectory_ptr)(t);
  }
  // int size = cal_XDes.size();

  // double tw0 = sequence[controlNodeTrajectoryNum[i]].tw0;
  // double twf = sequence[controlNodeTrajectoryNum[i]].twf;
  // VectorXd initialDes = sequence[controlNodeTrajectoryNum[i]].cal_XpreDes;
  // VectorXd finalDes = sequence[controlNodeTrajectoryNum[i]].cal_Xf;

  // for(int i=0; i<size; i++){
  //   des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));
  //   cal_XDes(i) = des(0) + cal_X0(i);
  //   cal_VxiDes(i) = des(1);
  //   cal_dVxiDes(i) = des(2);
  // }
}
