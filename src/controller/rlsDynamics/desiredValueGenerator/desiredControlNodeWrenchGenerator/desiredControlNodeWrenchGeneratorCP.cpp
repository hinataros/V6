/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::desiredControlNodeWrenchGeneratorCP(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredControlNodeWrenchGeneratorNum[controlNode]].tw0;
  double twf = sequence[desiredControlNodeWrenchGeneratorNum[controlNode]].twf;
  VectorXd initialDes = sequence[desiredControlNodeWrenchGeneratorNum[controlNode]].cal_FpreDes;
  VectorXd finalDes = sequence[desiredControlNodeWrenchGeneratorNum[controlNode]].cal_Ff;

  int start = 6*controlNode;
  for(int i=start; i<start+6; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    // cal_FDes(i) = des(0) + cal_F0(i);
    cal_FDes(i) = des(0);
  }
}
