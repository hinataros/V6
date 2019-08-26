/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::controlNodeTranslationSwingabs(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[controlNodeTranslationNum[controlNode]];
  double tf = twf[controlNodeTranslationNum[controlNode]];

  Vector3d des = Vector3d::Zero();
  for(int i=0; i<3; i++){
    des = makeSpline5(t-t0, tf, rfinCurabs[controlNode](i), rfabs[controlNode](i));

    if(i==2){
      if(round_cast(t-t0, 3)<round_cast(tf/2, 3)){
        des = makeSpline5(t-t0, tf/2, rfinCurabs[controlNode](i), rAp[controlNode]);
      }
      else{
        if(round_cast(t-t0, 3) == round_cast(tf/2, 3)){
          rfinCurabs[controlNode](i) = model->r[controlNode](i);
          // rfabs[controlNode](i) = rtd[controlNode](i);
        }

        des = makeSpline5(t-(t0+tf/2), tf/2, rfinCurabs[controlNode](i), rfabs[controlNode](i));
      }
    }

    rDes[controlNode](i) = des(0);
    cal_VDes(6*controlNode+i) = des(1);
    cal_dVDes(6*controlNode+i) = des(2);
  }
}
