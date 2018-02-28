/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseTranslationSequence(Config &config,Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, rBpreDes(i), rBf(i));
    rBDes(i) = des(0) + rB0(i);
    vBDes(i) = des(1);
    dvBDes(i) = des(2);
  }

  erB = rBDes - model.hoap2.limb[0].node[0].r;
  evB = vBDes - model.hoap2.limb[0].node[0].v;

  // velocityController
  vBRef = vBDes + KpvB*erB;

  dvBRef = dvBDes + KdvB*evB + KpvB*erB;
}
