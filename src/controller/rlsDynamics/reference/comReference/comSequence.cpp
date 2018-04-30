/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::comSequence(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, rCpreDes(i), rCf(i));
    rCDes(i) = des(0) + rC0(i);
    vCDes(i) = des(1);
    dvCDes(i) = des(2);
  }

  erC = rCDes - model.hoap2.all.rC;
  evC = vCDes - model.hoap2.all.vC;

  // velocityController
  vCRef = vCDes + KpC*erC;

  dvCRef = dvCDes + KdC*evC + KpC*erC;
}