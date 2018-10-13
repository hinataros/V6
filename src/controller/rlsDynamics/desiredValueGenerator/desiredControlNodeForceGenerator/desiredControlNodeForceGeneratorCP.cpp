/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredControlNodeForceGeneratorCP(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredControlNodeForceGeneratorNum[controlNode]].tw0;
  double twf = sequence[desiredControlNodeForceGeneratorNum[controlNode]].twf;
  VectorXd initialDes = sequence[desiredControlNodeForceGeneratorNum[controlNode]].cal_FpreDes;
  VectorXd finalDes = sequence[desiredControlNodeForceGeneratorNum[controlNode]].cal_Ff;

  int start = 6*controlNode;
  for(int i=start; i<start+6; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    // cal_FDes(i) = des(0) + cal_F0(i);
    cal_FDes(i) = des(0);
  }
}
