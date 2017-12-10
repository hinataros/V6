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

  mc_ptr = map_mc[mc_name];
  tc_ptr = map_tc[tc_name];

  info.sim.tw0 = t;
  info.sim.phase++;
}
