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
    dt << 1., 1., 1., 1., 1.;

    // double sopport
    // ******************************
    dtDS << 0.5, .5, .5, .5, .5, .5;

    alphDS << 0.5, .5, .5, .5, .5, .5;

    dtDSini <<
      0.,// dtDSini(0)=0 define
      alphDS(1)*dtDS(1),
      alphDS(2)*dtDS(2),
      alphDS(3)*dtDS(3),
      alphDS(4)*dtDS(4),
      alphDS(5)*dtDS(5);

    dtDSend <<
      (1 - alphDS(0))*dtDS(0),// dtDSend(0)=0 define
      (1 - alphDS(1))*dtDS(1),
      (1 - alphDS(2))*dtDS(2),
      (1 - alphDS(3))*dtDS(3),
      (1 - alphDS(4))*dtDS(4),
      0.;
    // ******************************

    rXeos.col(5) = rC0;
    rXeos.col(5)(0) = cal_X.segment(0, 3)(0);
    rXeos.col(5)(0) += 0.15;

    // ******************************
    // rf.col(4).head(2) = rC0.head(2);
    rf.col(4).head(2) = cal_X.segment(6, 3).head(2);
    rf.col(4)(0) += 0.15;
    rf.col(4)(1) -= 0.023;

    // rf.col(3).head(2) = rC0.head(2);
    rf.col(3).head(2) = cal_X.segment(0, 3).head(2);
    rf.col(3)(0) += 0.1;
    rf.col(3)(1) += 0.023;

    // rf.col(2).head(2) = rC0.head(2);
    rf.col(2).head(2) = cal_X.segment(6, 3).head(2);
    rf.col(2)(0) += 0.05;
    rf.col(2)(1) -= 0.023;

    // rf.col(1).head(2) = rC0.head(2);
    rf.col(1).head(2) = cal_X.segment(0, 3).head(2);
    // rf.col(1)(0) += 0.02;
    rf.col(1)(1) += 0.023;
    // ******************************


    rvrpd.col(5) = rXeos.col(5);

    for(int i=4; i>0; i--)
      rvrpd.col(i) = rf.col(i) - model.hoap2.ag/(wX*wX);

    rXeos.col(4) = rvrpd.col(4) + exp(-wX*dt(4))*(rXeos.col(5) - rvrpd.col(4));
    rXeos.col(3) = rvrpd.col(3) + exp(-wX*dt(3))*(rXeos.col(4) - rvrpd.col(3));
    rXeos.col(2) = rvrpd.col(2) + exp(-wX*dt(2))*(rXeos.col(3) - rvrpd.col(2));
    rXeos.col(1) = rvrpd.col(1) + exp(-wX*dt(1))*(rXeos.col(2) - rvrpd.col(1));
    rXeos.col(0) = rC0;

    rvrpd.col(0) = -rXeos.col(1)/(exp(wX*dt(0)) - 1) + rC0/(1 - exp(-wX*dt(0)));

    // double sopport
    // ******************************
    // final
    // ******************************
    // pos
    rXeoDS.col(5) = rvrpd.col(5);
    rXiniDS.col(5) = rvrpd.col(4) + exp(-wX*dtDSini(5))*(rXeos.col(5) - rvrpd.col(4));

    // vel
    drXeoDS.col(5) = wX*(rXeoDS.col(5) - rvrpd.col(5));
    drXiniDS.col(5) = wX*(rXiniDS.col(5) - rvrpd.col(4));

    // acc
    ddrXeoDS.col(5) = Vector3d::Zero();
    ddrXiniDS.col(5) = wX*wX*exp(-wX*dtDSini(5))*(rXeos.col(5) - rvrpd.col(4));
    // ******************************

    // pos
    rXeoDS.col(4) = rvrpd.col(4) + exp(wX*dtDSend(4))*(rXeos.col(4) - rvrpd.col(4));
    rXiniDS.col(4) = rvrpd.col(3) + exp(-wX*dtDSini(4))*(rXeos.col(4) - rvrpd.col(3));

    // vel
    drXeoDS.col(4) = wX*(rXeoDS.col(4) - rvrpd.col(4));
    drXiniDS.col(4) = wX*(rXiniDS.col(4) - rvrpd.col(3));
    // drXiniDS.col(4) = wX*exp(-wX*dtDSini(4))*(rXeos.col(4) - rvrpd.col(4));

    // acc
    ddrXeoDS.col(4) = wX*wX*exp(wX*dtDSend(4))*(rXeos.col(4) - rvrpd.col(4));
    ddrXiniDS.col(4) = wX*wX*exp(-wX*dtDSini(4))*(rXeos.col(4) - rvrpd.col(3));

    // pos
    rXeoDS.col(3) = rvrpd.col(3) + exp(wX*dtDSend(3))*(rXeos.col(3) - rvrpd.col(3));
    rXiniDS.col(3) = rvrpd.col(2) + exp(-wX*dtDSini(3))*(rXeos.col(3) - rvrpd.col(2));

    // vel
    drXeoDS.col(3) = wX*(rXeoDS.col(3) - rvrpd.col(3));
    drXiniDS.col(3) = wX*(rXiniDS.col(3) - rvrpd.col(2));
    // drXiniDS.col(3) = wX*exp(-wX*dtDSini(3))*(rXeos.col(3) - rvrpd.col(2));

    // acc
    ddrXeoDS.col(3) = wX*wX*exp(wX*dtDSend(3))*(rXeos.col(3) - rvrpd.col(3));
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

    // start
    // ******************************
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
  else if(round_cast(t, 3)>=2000&&round_cast(t, 3)<3000){
    stepPhase = 3;
    tw = t-(dt(0)+dt(1));
  }
  else if(round_cast(t, 3)>=3000&&round_cast(t, 3)<4000){
    stepPhase = 4;
    tw = t-(dt(0)+dt(1)+dt(2));
  }
  else{
    stepPhase = 5;
    tw = t-(dt(0)+dt(1)+dt(2)+dt(3));
  }

  if(round_cast(t, 3)<5000){

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
    rXDes = rXeos.col(5);
    drXDes = wX*(rXDes - rXeos.col(5));
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
  //   o(phaseDS);
  //   o(flagDS);
  //   o(rXDes);
  //   o(drXDes);
  //   o(rvrpd);
  //   o(rXeos);
  //   o(rXiniDS);
  //   o(rXeoDS);
  //   o(drXiniDS);
  //   o(drXeoDS);
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
