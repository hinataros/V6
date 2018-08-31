/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeState(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  state.num = -1; //smiyahara: 初期化をconfigurationManagerでやるため

  // previous state
  // ******************************
  state.rCpreDes = state.vCpreDes = Vector3d::Zero();
  state.rBpreDes = state.vBpreDes = Vector3d::Zero();
  state.xiBpreDes = state.xiBpreDes = Vector3d::Zero();

  state.rXpreDes = state.drXpreDes = Vector3d::Zero();
  state.cal_XpreDes = state.cal_VpreDes = VectorXd::Zero(6*info.eeNum);
}
