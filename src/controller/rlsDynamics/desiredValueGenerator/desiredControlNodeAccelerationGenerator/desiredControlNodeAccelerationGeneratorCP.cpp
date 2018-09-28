/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::desiredControlNodeAccelerationGeneratorCP(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].tw0;
  double twf = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].twf;
  VectorXd initialDes = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].cal_XpreDes;
  VectorXd finalDes = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].cal_Xf;

  int start = 6*controlNode;
  for(int i=start; i<start+6; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    cal_XDes(i) = des(0) + cal_X0(i);
    cal_VxiDes(i) = des(1);
    cal_dVxiDes(i) = des(2);
  }
}
