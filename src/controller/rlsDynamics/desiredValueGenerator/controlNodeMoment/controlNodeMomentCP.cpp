/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::controlNodeMomentCP(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[controlNodeForceNum[controlNode]];
  double tf = twf[controlNodeForceNum[controlNode]];

  Vector3d des = Vector3d::Zero();
  for(int i=0; i<3; i++){
    des = makeSpline5(t-t0, tf, npreDes[controlNode](i), nf[controlNode](i));

    // cal_FDes(6*controlNode+3+i) = des(0) + n0(i);
    cal_FDes(6*controlNode+3+i) = des(0);
  }
}
