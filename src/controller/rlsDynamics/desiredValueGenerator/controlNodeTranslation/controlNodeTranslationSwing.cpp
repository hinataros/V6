/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::controlNodeTranslationSwing(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[controlNodeTranslationNum[controlNode]];
  double tf = twf[controlNodeTranslationNum[controlNode]];

  // Vector3d des = Vector3d::Zero();
  Matrix3d des = Matrix3d::Zero();
  for(int i=0; i<3; i++){
    des.row(i) = makeSpline5(t-t0, tf, rfinCur[controlNode](i), rf[controlNode](i)).transpose();

    if(i==2){
      if(round_cast(t-t0, 3)<round_cast(tf/2, 3)){
        des.row(i) = makeSpline5(t-t0, tf/2, rfinCur[controlNode](i), rAp[controlNode]).transpose();
      }
      else{
        // if(round_cast(t-t0, 3) == round_cast(tf/2, 3)){
        //   rfinCur[controlNode](i) = model->r[controlNode](i) - r0[controlNode](i);
        //   // rf[controlNode](i) = rtd[controlNode](i);
        // }

        des.row(i) = makeSpline5(t-(t0+tf/2), tf/2, rAp[controlNode], rf[controlNode](i)).transpose();
      }
    }

    // rDes[controlNode](i) = des(0) + r0[controlNode](i);
    // cal_VDes(6*controlNode+i) = des(1);
    // cal_dVDes(6*controlNode+i) = des(2);
  }

  rDes[controlNode] = RB0*des.col(0) + r0[controlNode];
  cal_VDes.segment(6*controlNode, 3) = RB0*des.col(1);
  cal_dVDes.segment(6*controlNode, 3) = RB0*des.col(2);
  // 
  //
  // if(controlNode==1){
  //   cout << "desSpline===============" << endl;
  //   o(rfinCur[controlNode]);
  //   o(model->r[controlNode]);
  //   o(model->r[controlNode] - r0[controlNode]);
  //   o(rf[controlNode]);
  //   o(des.col(0));
  //   o(rDes[controlNode]);
  //   cout << "========================" << endl;
  //
  // }
}
