/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::resizeState()
{
  if(debug) DEBUG;

  state.rCpreDes = state.vCpreDes = Vector3d::Zero();
  state.rBpreDes = state.vBpreDes = Vector3d::Zero();
  state.xiBpreDes = state.xiBpreDes = Vector3d::Zero();

  state.rXpreDes = state.drXpreDes = Vector3d::Zero();
  state.cal_XpreDes = state.cal_VpreDes = VectorXd::Zero(6*info->controlNodeNum);
}
