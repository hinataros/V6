/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::baseRotationCP(const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[baseRotationNum];
  double tf = twf[baseRotationNum];

  Vector3d des = makeSpline5(t-t0, tf, qBpreDes.w, qBf.w);

  qBDes.w = des(0);
  dqBDes.w = des(1);
  ddqBDes.w = des(2);

  for(int i=0; i<3; i++){
    des = makeSpline5(t-t0, tf, qBpreDes.v(i), qBf.v(i));

    qBDes.v(i) = des(0);
    dqBDes.v(i) = des(1);
    ddqBDes.v(i) = des(2);
  }

  qBDes *= qB0;

  RBDes = qBDes.rotationMatrix();
  wBDes = Quaternion4d::dq2w(qBDes, dqBDes);
  dwBDes = Quaternion4d::ddq2dw(qBDes, dqBDes, ddqBDes);
}
