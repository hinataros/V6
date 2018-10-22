/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredControlNodeMotionGeneratorWalking(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].tw0;
  double twf = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].twf;
  VectorXd initialDes = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].cal_XpreDesabs;
  VectorXd finalDes = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].cal_Xfabs;
  VectorXd tdDes = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].cal_Xtd;

  int start = 6*controlNode;
  for(int i=start, j=0; i<start+6; i++, j++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    if(j==2){
      if(round_cast(t-tw0, 3)<round_cast(twf/2, 3)){
        des = makeSpline5(t-tw0, twf/2, initialDes(i), finalDes(i));
      }
      else{
        if(round_cast(t-tw0, 3) == round_cast(twf/2, 3)){
          initialDes(i) = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].cal_XpreDesabs(i) = model->cal_X(i);
          finalDes(i) = sequence[desiredControlNodeMotionGeneratorNum[controlNode]].cal_Xfabs(i) = tdDes(i);
        }

        des = makeSpline5(t-(tw0+twf/2), twf/2, initialDes(i), finalDes(i));
      }
    }

    cal_XDes(i) = des(0);
    cal_VxiDes(i) = des(1);
    cal_dVxiDes(i) = des(2);
  }

  cal_VDes.segment(6*controlNode, 6) <<
    cal_VxiDes.segment(6*controlNode, 3),
    dxi2w(cal_VxiDes.segment(6*controlNode+3, 3), cal_XDes.segment(6*controlNode+3, 3));
  cal_dVDes.segment(6*controlNode, 6) <<
    cal_dVxiDes.segment(6*controlNode, 3),
    ddxi2dw(cal_dVxiDes.segment(6*controlNode+3, 3), cal_XDes.segment(6*controlNode+3, 3), cal_VxiDes.segment(6*controlNode+3, 3));
}
