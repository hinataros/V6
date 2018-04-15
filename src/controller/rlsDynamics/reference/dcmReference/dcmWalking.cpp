 /**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmWalking(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  if(t==0.){
    dt << 1., 1., 1.;
    rXeos.col(3) << 0.04, 0., 0.;
    rXeos.col(3) += rC0;

    rf.col(2) = cal_X.segment(6, 3);
    rf.col(2)(0) += 0.04;
    rf.col(1) = cal_X.segment(0, 3);

    for(int i=2; i>0; i--)
      rvrpd.col(i) = rf.col(i) - model.hoap2.ag/(wX*wX);

    rXeos.col(2) = rvrpd.col(2) + exp(-wX*dt(2))*(rXeos.col(3) - rvrpd.col(2));
    rXeos.col(1) = rvrpd.col(1) + exp(-wX*dt(1))*(rXeos.col(2) - rvrpd.col(1));
    rXeos.col(0) = rC0;

    rvrpd.col(0) = -rXeos.col(1)/(exp(wX*dt(0)) - 1) + rC0/(1 - exp(-wX*dt(0)));
  }

  // o(wX);
  // o(rvrpd.col(info.sim.phase-1));
  // o(rXeos.col(info.sim.phase));
  // gc;
  if(round_cast(t, 3)<3000){
    rXDes = rvrpd.col(info.sim.phase-1) +
      exp(wX*(t-info.sim.tw0-dt(info.sim.phase-1)))*(rXeos.col(info.sim.phase) - rvrpd.col(info.sim.phase-1));
    // drXDes = wX*exp(wX*(t-info.sim.tw0-dt(info.sim.phase-1)))*(rXeos.col(info.sim.phase) - rvrpd.col(info.sim.phase-1));
    drXDes = wX*(rXDes - rvrpd.col(info.sim.phase-1));
  }
  else{
    rXDes = rXeos.col(3);
    drXDes = wX*(rXDes - rXeos.col(3));
  }

  // if(round_cast(t, 3)<1000){
  //   rXDes = rvrpd.col(info.sim.phase-1) +
  //     exp(wX*(t-info.sim.tw0-dt(info.sim.phase-1)))*(rXeos.col(info.sim.phase) - rvrpd.col(info.sim.phase-1));
  //   drXDes = wX*(rXDes - rvrpd.col(info.sim.phase-1));
  // }
  // else{
  //   rXDes = rXeos.col(1);
  //   drXDes = wX*(rXDes - rXeos.col(1));
  // }
  // if(t==0.||round_cast(t, 3)==1000||round_cast(t, 3)==2000||round_cast(t, 3)==3000){
  // if(t==0.||round_cast(t, 3)==3000||round_cast(t, 3)==6000||round_cast(t, 3)==9000){
  //   o("In reference");
  //   o(t);
  //   o(info.sim.phase);
  //   o(rC0);
  //   o(rXeos);
  //   o(rf);
  //   o(rvrpd);

  //   o(rXDes);
  //   o(drXDes);
  //   gc;
  // }


  // for(int i=0; i<3; i++){
  //   des = makeSpline5(t-info.sim.tw0, info.sim.twf, rXpreDes(i), rXf(i));
  //   rXDes(i) = des(0) + rX0(i);
  //   drXDes(i) = des(1);
  // }

  eX = rXDes - rX;

  drXRef = drXDes + KX*eX;
}
