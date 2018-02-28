 /**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmSequence(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, rXpreDes(i), rXf(i));
    rXDes(i) = des(0) + rX0(i);
    drXDes(i) = des(1);
  }

  eX = rXDes - rX;

  drXRef = drXDes + KX*eX;
}
