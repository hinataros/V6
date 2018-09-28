/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::desiredControlNodeAccelerationGeneratorWalking(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].tw0;
  double twf = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].twf;
  VectorXd initialDes = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].cal_XpreDes;
  VectorXd finalDes = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].cal_Xf;
  VectorXd tdDes = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].cal_Xtd;

  int start = 6*controlNode;
  for(int i=start, j=0; i<start+6; i++, j++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    if(j==2){
      if(round_cast(t-tw0, 3)<round_cast(twf/2, 3)){
        des = makeSpline5(t-tw0, twf/2, initialDes(i), finalDes(i));
      }
      else{
        if(round_cast(t-tw0, 3) == round_cast(twf/2, 3)){
          initialDes(i)
            = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].cal_XpreDes(i) = finalDes(i);
          finalDes(i)
            = sequence[desiredControlNodeAccelerationGeneratorNum[controlNode]].cal_Xf(i) = tdDes(i);
        }

        des = makeSpline5(t-(tw0+twf/2), twf/2, initialDes(i), finalDes(i));
      }
    }

    cal_XDes(i) = des(0) + cal_X0(i);
    cal_VxiDes(i) = des(1);
    cal_dVxiDes(i) = des(2);
  }
}
