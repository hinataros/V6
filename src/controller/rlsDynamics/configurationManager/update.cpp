/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

// bool RLS::RlsDynamics::resetState(Config &config, Info &info, Model &model, double &t)
// {
//   if(config.flag.debug) DEBUG;

//   rCpreState = model.hoap2.all.rC - rC0;
//   vCpreState = model.hoap2.all.vC;

//   rBpreState = model.hoap2.limb[0].node[0].r - rB0;
//   vBpreState = model.hoap2.limb[0].node[0].v;
//   xiBpreState = R2xi(model.hoap2.limb[0].node[0].R) - xiB0;
//   dxiBpreState = w2dxi(model.hoap2.limb[0].node[0].w, R2xi(model.hoap2.limb[0].node[0].R));

//   rXpreState = rX - rX0;
//   // smiyahara: いつか変える
//   drXpreState = drXDes;

//   cal_XpreState = cal_X - cal_X0;
//   cal_VpreState = cal_V;

//   readWork(config, info, "State", info.sim.state);

//   info.sim.trev = t;

//   return true;
// }

void RLS::RlsDynamics::updateSequence(const double &t, const int num)
{
  if(debug) DEBUG;

  sequence[num].rCpreDes = sequence[num].rCf;

  sequence[num].rBpreDes = sequence[num].rBf;
  sequence[num].xiBpreDes = sequence[num].xiBf;

  sequence[num].rXpreDes = sequence[num].rXf;

  sequence[num].cal_XpreDes = sequence[num].cal_Xf;

  sequence[num].cal_FextpreDes = sequence[num].cal_Fextf;

  sequence[num].tw0 = t;
}
