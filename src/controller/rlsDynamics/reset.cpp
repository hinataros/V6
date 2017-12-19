#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reset(Config &config, Info &info, double &t)
{
  if(config.flag.debug) DEBUG;

  // smiyahara: 1ステップ目は初期化と同義
  rCtemp = rCf;

  rBtemp = rBf;
  xiBtemp = xiBf;

  cal_Xtemp = cal_Xf;

  readWork(config, info);

  motionController_ptr = map_motionController[motionControllerName];
  momentumController_ptr = map_momentumController[momentumControllerName];
  forceController_ptr = map_forceController[forceControllerName];
  torqueController_ptr = map_torqueController[torqueControllerName];
  inverseDynamicsController_ptr = map_inverseDynamicsController[inverseDynamicsControllerName];

  info.sim.tw0 = t;
  info.sim.phase++;
}
