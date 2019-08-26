/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredControlNodeMotionGeneratorCP(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].tw0;
  double twf = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].twf;
  VectorXd initialDes = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].cal_XpreDes;
  VectorXd finalDes = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].cal_Xf;

  int start = 6*controlNode;
  for(int i=start; i<start+6; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    cal_XDes(i) = des(0) + cal_X0(i);
    cal_VxiDes(i) = des(1);
    cal_dVxiDes(i) = des(2);
  }

  // cal_VDes.segment(6*controlNode, 6) <<
  //   model->cal_VxiDes.segment(6*controlNode, 3),
  //   dxi2w(model->cal_VxiDes.segment(6*controlNode+3, 3), model->cal_X.segment(6*controlNode+3, 3));
  // cal_dVDes.segment(6*controlNode, 6) <<
  //   cal_dVxiDes.segment(6*controlNode, 3),
  //   ddxi2dw(cal_dVxiDes.segment(6*controlNode+3, 3), model->cal_X.segment(6*controlNode+3, 3), w2dxi(model->cal_V.segment(6*controlNode+3, 3), model->cal_X.segment(6*controlNode+3, 3)));

  cal_VDes.segment(6*controlNode, 6) <<
    cal_VxiDes.segment(6*controlNode, 3),
    dxi2w(cal_VxiDes.segment(6*controlNode+3, 3), cal_XDes.segment(6*controlNode+3, 3));
  cal_dVDes.segment(6*controlNode, 6) <<
    cal_dVxiDes.segment(6*controlNode, 3),
    ddxi2dw(cal_dVxiDes.segment(6*controlNode+3, 3), cal_XDes.segment(6*controlNode+3, 3), cal_VxiDes.segment(6*controlNode+3, 3));
}
