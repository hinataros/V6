/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::controlNodeRotationCurCP(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[controlNodeRotationNum[controlNode]];
  double tf = twf[controlNodeRotationNum[controlNode]];

  Vector3d des = makeSpline5(t-t0, tf, qfinCur[controlNode].w, qf[controlNode].w);

  qDes[controlNode].w = des(0);
  dqDes[controlNode].w = des(1);
  ddqDes[controlNode].w = des(2);

  for(int i=0; i<3; i++){
    des = makeSpline5(t-t0, tf, qfinCur[controlNode].v(i), qf[controlNode].v(i));

    qDes[controlNode].v(i) = des(0);
    dqDes[controlNode].v(i) = des(1);
    ddqDes[controlNode].v(i) = des(2);
  }

  qDes[controlNode] *= q0[controlNode];

  RDes[controlNode] = qDes[controlNode].rotationMatrix();
  cal_VDes.segment(6*controlNode+3, 3) = Quaternion4d::dq2w(qDes[controlNode], dqDes[controlNode]);
  cal_dVDes.segment(6*controlNode+3, 3) = Quaternion4d::ddq2dw(qDes[controlNode], dqDes[controlNode], ddqDes[controlNode]);
}
