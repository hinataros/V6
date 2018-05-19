 /**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmDSWalking(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  if(t==0.){
    dt << 1., 1., 1.;

    // double sopport
    // ******************************
    dtDS << 0.5, .5, .5, .5;
    alphDS << 0.5, .5, .5, .5;

    dtDSini <<
      0.,// dtDSini(0)=0 define
      alphDS(1)*dtDS(1),
      alphDS(2)*dtDS(2),
      alphDS(3)*dtDS(3);

    dtDSend <<
      (1 - alphDS(0))*dtDS(0),// dtDSend(0)=0 define
      (1 - alphDS(1))*dtDS(1),
      (1 - alphDS(2))*dtDS(2),
      0.;
    // ******************************

    rXeos.col(3) = rC0;
    // rXeos.col(3)(0) += 0.01;
    rXeos.col(3)(1) -= 0.015;
    // rXeos.col(3)(0) += 0.04;
    // rXeos.col(3)(0) += 0.1;

    // // ******************************
    // rf.col(2) = cal_X.segment(6, 3);
    // rf.col(2)(0) += rC0(0);
    // rf.col(2)(1) -= 0.01;

    // rf.col(1) = cal_X.segment(0, 3);
    // rf.col(1)(0) += rC0(0);
    // rf.col(1)(1) += 0.01;
    // // ******************************
    // ******************************
    rf.col(2).head(2) = rC0.head(2);
    rf.col(2)(1) += 0.02;

    rf.col(1).head(2) = rC0.head(2);
    rf.col(1)(1) -= 0.02;
    // ******************************

    // rf.col(2)(0) += 0.01;
    // rf.col(2)(0) += .04;
    // rf.col(2)(0) += .1;

    rvrpd.col(3) = rXeos.col(3);

    for(int i=2; i>0; i--)
      rvrpd.col(i) = rf.col(i) - model.hoap2.ag/(wX*wX);

    rXeos.col(2) = rvrpd.col(2) + exp(-wX*dt(2))*(rXeos.col(3) - rvrpd.col(2));
    rXeos.col(1) = rvrpd.col(1) + exp(-wX*dt(1))*(rXeos.col(2) - rvrpd.col(1));
    rXeos.col(0) = rC0;

    rvrpd.col(0) = -rXeos.col(1)/(exp(wX*dt(0)) - 1) + rC0/(1 - exp(-wX*dt(0)));

    // double sopport
    // ******************************
    // pos
    rXeoDS.col(3) = rvrpd.col(3);
    rXiniDS.col(3) = rvrpd.col(2) + exp(-wX*dtDSini(3))*(rXeos.col(3) - rvrpd.col(2));

    // vel
    drXeoDS.col(3) = wX*(rXeoDS.col(3) - rvrpd.col(3));
    drXiniDS.col(3) = wX*(rXiniDS.col(3) - rvrpd.col(2));
    // drXiniDS.col(3) = wX*exp(-wX*dtDSini(3))*(rXeos.col(3) - rvrpd.col(2));

    // acc
    ddrXeoDS.col(3) = Vector3d::Zero();
    ddrXiniDS.col(3) = wX*wX*exp(-wX*dtDSini(3))*(rXeos.col(3) - rvrpd.col(2));

    // pos
    rXeoDS.col(2) = rvrpd.col(2) + exp(wX*dtDSend(2))*(rXeos.col(2) - rvrpd.col(2));
    rXiniDS.col(2) = rvrpd.col(1) + exp(-wX*dtDSini(2))*(rXeos.col(2) - rvrpd.col(1));

    // vel
    drXeoDS.col(2) = wX*(rXeoDS.col(2) - rvrpd.col(2));
    drXiniDS.col(2) = wX*(rXiniDS.col(2) - rvrpd.col(1));
    // drXeoDS.col(2) = wX*exp(wX*dtDSend(2))*(rXeos.col(2) - rvrpd.col(2));
    // drXiniDS.col(2) = wX*exp(-wX*dtDSini(2))*(rXeos.col(2) - rvrpd.col(1));

    // acc
    ddrXeoDS.col(2) = wX*wX*exp(wX*dtDSend(2))*(rXeos.col(2) - rvrpd.col(2));
    ddrXiniDS.col(2) = wX*wX*exp(-wX*dtDSini(2))*(rXeos.col(2) - rvrpd.col(1));

    // pos
    rXeoDS.col(1) = rvrpd.col(1) + exp(wX*dtDSend(1))*(rXeos.col(1) - rvrpd.col(1));
    rXiniDS.col(1) = rvrpd.col(0) + exp(-wX*dtDSini(1))*(rXeos.col(1) - rvrpd.col(0));

    // vel
    drXeoDS.col(1) = wX*(rXeoDS.col(1) - rvrpd.col(1));
    drXiniDS.col(1) = wX*(rXiniDS.col(1) - rvrpd.col(0));
    // drXeoDS.col(1) = wX*exp(wX*dtDSend(1))*(rXeos.col(1) - rvrpd.col(1));
    // drXiniDS.col(1) = wX*exp(-wX*dtDSini(1))*(rXeos.col(1) - rvrpd.col(0));

    // acc
    ddrXeoDS.col(1) = wX*wX*exp(wX*dtDSend(1))*(rXeos.col(1) - rvrpd.col(1));
    ddrXiniDS.col(1) = wX*wX*exp(-wX*dtDSini(1))*(rXeos.col(1) - rvrpd.col(0));

    // pos
    rXeoDS.col(0) = rvrpd.col(0) + exp(wX*dtDSend(0))*(rXeos.col(0) - rvrpd.col(0));
    rXiniDS.col(0) = rXeos.col(0);// assumption

    // vel
    drXeoDS.col(0) = wX*(rXeoDS.col(0) - rvrpd.col(0));
    drXiniDS.col(0) = Vector3d::Zero();// assumption
    // drXeoDS.col(0) = wX*exp(wX*dtDSend(0))*(rXeos.col(0) - rvrpd.col(0));

    // acc
    ddrXeoDS.col(0) = wX*wX*exp(wX*dtDSend(0))*(rXeos.col(0) - rvrpd.col(0));
    ddrXiniDS.col(0) = Vector3d::Zero();// assumption

    // ******************************
  }

  double tw = 0.;
  int stepPhase = 1;
  if(round_cast(t, 3)<1000){
    stepPhase = 1;
    tw = t;
  }
  else if(round_cast(t, 3)>=1000&&round_cast(t, 3)<2000){
    stepPhase = 2;
    tw = t-dt(0);
  }
  else{
    stepPhase = 3;
    tw = t-(dt(0)+dt(1));
  }

  // double tw = t - info.sim.tw0;
  if(round_cast(t, 3)<3000){

    // single sopport
    // ******************************
    rXDes = rvrpd.col(stepPhase-1) +
      exp(wX*(tw-dt(stepPhase-1)))*(rXeos.col(stepPhase) - rvrpd.col(stepPhase-1));

    drXDes = wX*(rXDes - rvrpd.col(stepPhase-1));

    // double sopport
    // ******************************
    if(flagDS==false&&round_cast(tw, 3) ==
       (round_cast(dt(stepPhase-1), 3) - round_cast(dtDSini(stepPhase), 3))){
      flagDS = true;
      tDS0 = t;

      phaseDS++;
    }

    if(flagDS){
      double twDS = t-tDS0;

      if(round_cast(twDS,3)==round_cast(dtDSini(phaseDS),3)+round_cast(dtDSend(phaseDS),3))
        flagDS = false;

      for(int i=0; i<3; i++){
        // des = makeSpline3(twDS, dtDSini(phaseDS)+dtDSend(phaseDS),
        //                   rXiniDS.col(phaseDS)(i),
        //                   drXiniDS.col(phaseDS)(i),
        //                   rXeoDS.col(phaseDS)(i),
        //                   drXeoDS.col(phaseDS)(i));
        des = makeSpline5(twDS, dtDSini(phaseDS)+dtDSend(phaseDS),
                          rXiniDS.col(phaseDS)(i),
                          drXiniDS.col(phaseDS)(i),
                          ddrXiniDS.col(phaseDS)(i),
                          rXeoDS.col(phaseDS)(i),
                          drXeoDS.col(phaseDS)(i),
                          ddrXeoDS.col(phaseDS)(i));

        rXDes(i) = des(0);
        drXDes(i) = des(1);
      }
    }
  }
  else{
    rXDes = rXeos.col(3);
    drXDes = wX*(rXDes - rXeos.col(3));
  }

  // if(
  //    round_cast(t, 3)==0||
  //    round_cast(t, 3)==250||
  //    round_cast(t, 3)==750||
  //    round_cast(t, 3)==1000||
  //    round_cast(t, 3)==1250||
  //    round_cast(t, 3)==1750||
  //    round_cast(t, 3)==2000||
  //    round_cast(t, 3)==2250||
  //    // round_cast(t, 3)==2750||
  //    round_cast(t, 3)==2500||
  //    round_cast(t, 3)==3000
  //    ){
  //   o(round_cast(t, 3));
  //   // o(phaseDS);
  //   // o(flagDS);
  //   // o(rXDes);
  //   // o(drXDes);
  //   // o(rvrpd);
  //   // o(rXeos);
  //   // o(rXiniDS);
  //   // o(rXeoDS);
  //   // o(drXiniDS);
  //   // o(drXeoDS);
  //   o(ddrXiniDS);
  //   o(ddrXeoDS);
  //   // o(dtDSini(phaseDS)+dtDSend(phaseDS));
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
