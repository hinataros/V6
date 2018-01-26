/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmReference(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  if(info.sim.state==-1||info.sim.state==0)
    for(int i=0; i<3; i++){
      des = makeSpline5(t-info.sim.tw0, info.sim.twf, rXpreDes(i), rXf(i));
      rXDes(i) = des(0) + rX0(i);
      drXDes(i) = des(1);
    }

  if(info.sim.state==1){
    rXDes = model.hoap2.all.rC;
    drXDes = model.hoap2.all.vC;
  }

  if(info.sim.state==2){
    for(int i=0; i<3; i++){
      // des = makeSpline5(t-info.sim.trev, info.sim.trecf, rXpreState(i), drXpreState(i), 0., rXf(i), 0., 0.);
      des = makeSpline5(t-info.sim.trev, info.sim.trecf, rXpreState(i), rXf(i));
      rXDes(i) = des(0) + rX0(i);
      drXDes(i) = des(1);
    }

    rXDes = model.hoap2.all.rC + (1 - exp(-wX*(t-info.sim.trev)))*(rXDes - model.hoap2.all.rC);
    drXDes = model.hoap2.all.vC + (1 - exp(-wX*(t-info.sim.trev)))*(drXDes - model.hoap2.all.vC);
  }

  eX = rXDes - rX;

  drXRef = drXDes + KX*eX;
}
