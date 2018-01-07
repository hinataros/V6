/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

bool RLS::RlsDynamics::resetState(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  rCpreState = model.hoap2.all.rC - rC0;
  vCpreState = model.hoap2.all.vC;

  rBpreState = model.hoap2.limb[0].node[0].r - rB0;
  vBpreState = model.hoap2.limb[0].node[0].v;
  xiBpreState = R2xi(model.hoap2.limb[0].node[0].R) - xiB0;
  dxiBpreState = w2dxi(model.hoap2.limb[0].node[0].w, R2xi(model.hoap2.limb[0].node[0].R));

  cal_XpreState = cal_X - cal_X0;
  cal_VpreState = cal_V;

  readWork(config, info, "State", info.sim.state);

  info.sim.trev = t;

  return true;
}

bool RLS::RlsDynamics::resetSequence(Config &config, Info &info, double &t)
{
  if(config.flag.debug) DEBUG;

  rCpreDes = rCf;

  rBpreDes = rBf;
  xiBpreDes = xiBf;

  cal_XpreDes = cal_Xf;

  cal_FextpreDes = cal_Fextf;

  readWork(config, info, "Sequence", info.sim.phase);

  info.sim.tw0 = t;
  info.sim.phase++;

  return true;
}
