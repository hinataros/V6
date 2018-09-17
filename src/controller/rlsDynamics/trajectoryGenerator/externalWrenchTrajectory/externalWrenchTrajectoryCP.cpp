/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::externalWrenchTrajectoryCP(const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[externalWrenchTrajectoryNum].tw0;
  double twf = sequence[externalWrenchTrajectoryNum].twf;
  Vector6d initialDes = sequence[externalWrenchTrajectoryNum].cal_FextpreDes;
  Vector6d finalDes = sequence[externalWrenchTrajectoryNum].cal_Fextf;

  for(int i=0; i<6; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    cal_FextDes(i) = des(0);
  }
}
