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

  // setting
  // straight walk on flat ground
  // ********************************
  double tstab = 2.;

  // double dtstep = .3;
  // double dtDSstep = .1;
  // double alphDSstep = .5;
  // double dtstep = .5;
  // double dtDSstep = .2;
  // double alphDSstep = .5;
  double dtstep = .8;
  double dtDSstep = .3;
  double alphDSstep = .5;
  // double dtstep = .6;
  // double dtDSstep = .4;
  // double alphDSstep = .5;

  // double steplength = 0.01;
  double steplength = 0.045;

  double offset = 0.;
  // offset = 0.015;
  offset = 0.01;
  // offset = 0.011;

  // offset = 1.e-3;
  // offset = 1.e-2;
  double height = 0.;
  // ********************************

  // // ********************************
  // double tstab = 2.;

  // double dtstep = 1.5;
  // double dtDSstep = .5;
  // double alphDSstep = .5;

  // double steplength = 0.07;

  // double height = 0.01;

  // double offset = 0.;
  // offset = 0.015;

  // // offset = 1.e-3;
  // // offset = 1.e-2;
  // // ********************************

  double tf = tstab + dtstep*stepNum;

  if(t==0.){
    for(int i=0; i<stepNum; i++){
      dt(i) = dtstep;
    }
    for(int i=0; i<stepNum+1; i++){
      dtDS(i) = dtDSstep;
      alphDS(i) = alphDSstep;
    }

    for(int i=0; i<stepNum+1; i++){
      // dtDSini(0) = 0 define
      if(i!=0)
        dtDSini(i) = alphDS(i)*dtDS(i);

      // dtDSend(stepNum) = 0 define
      if(i!=stepNum)
        dtDSend(i) = (1 - alphDS(i))*dtDS(i);
    }

    double heighttemp = 0.;
    rf.col(1).head(2) = cal_X.segment(0, 3).head(2);
    rf.col(1)(1) += offset;
    rf.col(1)(2) += heighttemp; heighttemp += height;

    rf.col(2).head(2) = cal_X.segment(6, 3).head(2);
    rf.col(2)(1) -= offset;
    rf.col(2)(2) += heighttemp; heighttemp += height;

    rf.col(3).head(2) = cal_X.segment(0, 3).head(2);
    rf.col(3)(1) += offset;
    rf.col(3)(2) += heighttemp; heighttemp += height;

    rf.col(4).head(2) = cal_X.segment(6, 3).head(2);
    rf.col(4)(1) -= offset;
    rf.col(4)(2) += heighttemp; heighttemp += height;

    rf.col(5).head(2) = cal_X.segment(0, 3).head(2);
    rf.col(5)(1) += offset;
    rf.col(5)(2) += heighttemp; heighttemp += height;

    rf.col(6).head(2) = cal_X.segment(6, 3).head(2);
    rf.col(6)(1) -= offset;
    rf.col(6)(2) += heighttemp; heighttemp += height;

    rf.col(7).head(2) = cal_X.segment(0, 3).head(2);
    rf.col(7)(1) += offset;
    rf.col(7)(2) += heighttemp; heighttemp += height;

    rf.col(8).head(2) = cal_X.segment(6, 3).head(2);
    rf.col(8)(1) -= offset;
    rf.col(8)(2) += heighttemp;

    rf.col(9).head(2) = rC0.head(2);
    rf.col(9)(0) = cal_X.segment(0, 3)(0);
    rf.col(9)(2) += heighttemp;;
    // ******************************

    rXeos.col(10) = rC0;
    rXeos.col(10)(0) = cal_X.segment(0, 3)(0);
    rXeos.col(10)(2) += heighttemp;

    double temp = 0.;
    for(int i=2; i<stepNum-1; i++){
      temp += steplength;

      rf.col(i)(0) += temp;
    }

    rf.col(stepNum-1)(0) += temp;
    rXeos.col(stepNum)(0) += temp;

    rvrpd.col(stepNum) = rXeos.col(stepNum);

    for(int i=stepNum-1; i>0; i--){
      rvrpd.col(i) = rf.col(i) - model.hoap2.ag/(wX*wX);
      rXeos.col(i) = rvrpd.col(i) + exp(-wX*dt(i))*(rXeos.col(i+1) - rvrpd.col(i));
    }

    rXeos.col(0) = rC0;
    rvrpd.col(0) = -rXeos.col(1)/(exp(wX*dt(0)) - 1) + rC0/(1 - exp(-wX*dt(0)));

    // double sopport
    // ******************************
    // final
    rXeoDS.col(stepNum) = rvrpd.col(stepNum);
    rXiniDS.col(stepNum) = rvrpd.col(stepNum-1) + exp(-wX*dtDSini(stepNum))*(rXeos.col(stepNum) - rvrpd.col(stepNum-1));
    // ******************************
    drXeoDS.col(stepNum) = wX*(rXeoDS.col(stepNum) - rvrpd.col(stepNum));
    drXiniDS.col(stepNum) = wX*(rXiniDS.col(stepNum) - rvrpd.col(stepNum-1));

    // ******************************
    ddrXeoDS.col(stepNum) = Vector3d::Zero();
    ddrXiniDS.col(stepNum) = wX*wX*exp(-wX*dtDSini(stepNum))*(rXeos.col(stepNum) - rvrpd.col(stepNum-1));

    for(int i=stepNum-1; i>0; i--){
      rXeoDS.col(i) = rvrpd.col(i) + exp(wX*dtDSend(i))*(rXeos.col(i) - rvrpd.col(i));
      rXiniDS.col(i) = rvrpd.col(i-1) + exp(-wX*dtDSini(i))*(rXeos.col(i) - rvrpd.col(i-1));

      drXeoDS.col(i) = wX*(rXeoDS.col(i) - rvrpd.col(i));
      drXiniDS.col(i) = wX*(rXiniDS.col(i) - rvrpd.col(i-1));

      ddrXeoDS.col(i) = wX*wX*exp(wX*dtDSend(i))*(rXeos.col(i) - rvrpd.col(i));
      ddrXiniDS.col(i) = wX*wX*exp(-wX*dtDSini(i))*(rXeos.col(i) - rvrpd.col(i-1));
    }

    // start
    // ******************************
    rXeoDS.col(0) = rvrpd.col(0) + exp(wX*dtDSend(0))*(rXeos.col(0) - rvrpd.col(0));
    rXiniDS.col(0) = rXeos.col(0);// assumption
    // ******************************
    drXeoDS.col(0) = wX*(rXeoDS.col(0) - rvrpd.col(0));
    drXiniDS.col(0) = Vector3d::Zero();// assumption
    // ******************************
    ddrXeoDS.col(0) = wX*wX*exp(wX*dtDSend(0))*(rXeos.col(0) - rvrpd.col(0));
    ddrXiniDS.col(0) = Vector3d::Zero();// assumption
  }


  double ts = t - tstab;
  if(round_cast(t, 3)<round_cast(tstab, 3)){
    for(int i=0; i<3; i++){
      des = makeSpline5(t-info.sim.tw0, info.sim.twf, rXpreDes(i), rXf(i));
      rXDes(i) = des(0) + rX0(i);
      drXDes(i) = des(1);
    }
  }
  else if(round_cast(t, 3)<round_cast(tf, 3)){
    tstep = ts - tstep0;
    if(round_cast(tstep, 3)>=round_cast(dt(stepPhase), 3)){
      tstep = 0.;
      tstep0 += dt(stepPhase);
      stepPhase++;
    }

    // single sopport
    // ******************************
    rXDes = rvrpd.col(stepPhase) +
      exp(wX*(tstep-dt(stepPhase)))*(rXeos.col(stepPhase+1) - rvrpd.col(stepPhase));

    drXDes = wX*(rXDes - rvrpd.col(stepPhase));

    // double sopport
    // ******************************
    if(flagDS==false&&round_cast(tstep, 3) ==
       (round_cast(dt(stepPhase), 3) - round_cast(dtDSini(stepPhase+1), 3))){
      flagDS = true;
      tDS0 = ts;

      phaseDS++;
    }

    if(flagDS){
      double twDS = ts-tDS0;

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
    rXDes = rXeos.col(stepNum);
    drXDes = wX*(rXDes - rXeos.col(stepNum));
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
