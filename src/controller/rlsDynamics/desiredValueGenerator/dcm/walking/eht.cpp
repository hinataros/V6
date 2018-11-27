 /**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::eht(const double &t)
{
  if(debug) DEBUG;

  if(fext.norm()!=0.){
    // backward calculation
    // ****************************************************************
    Vector3d toeOffset = (Vector3d()<<ht_config.toe, 0., 0.).finished();
    Vector3d heelOffset = (Vector3d()<<ht_config.heel, 0., 0.).finished();

    Vector3d Dzvrp = (Vector3d()<<0., 0., g/(wX*wX)).finished();

    Vector3d rHextDes = fext/(model->M*wX*wX);

    // final desired DCM position
    // rXTH.col(ht_config.stepNum) is unused
    rXHT.col(ht_config.stepNum) = rf.col(ht_config.stepNum) + Dzvrp - rHextDes;

    // final desired VRP
    // rvrpTd.col(ht_config.stepNum) is unused
    rvrpHd.col(ht_config.stepNum) = rXHT.col(ht_config.stepNum);

    for(int i=ht_config.stepNum-1; i>0; i--){
      if(i==ht_config.stepNum-1){
        rndvrpTd.col(i) = rf.col(i) + Dzvrp;
        rndvrpHd.col(i) = rf.col(i) + Dzvrp;
      }
      else if(i==ht_config.stepNum-2){
        rndvrpTd.col(i) = rf.col(i) + Dzvrp;
        rndvrpHd.col(i) = rf.col(i) + heelOffset + Dzvrp;
      }
      else if(i==1){
        rndvrpTd.col(i) = rf.col(i) + toeOffset + Dzvrp;
        rndvrpHd.col(i) = rf.col(i) + Dzvrp;
      }
      else{
        rndvrpTd.col(i) = rf.col(i) + toeOffset + Dzvrp;
        rndvrpHd.col(i) = rf.col(i) + heelOffset + Dzvrp;
      }

      rvrpTd.col(i) = rndvrpTd.col(i) - rHextDes;
      rvrpHd.col(i) = rndvrpHd.col(i) - rHextDes;

      rXTH.col(i) = rvrpTd.col(i) + exp(-wX*dtTH(i))*(rXHT.col(i+1) - rvrpTd.col(i));
      rXHT.col(i) = rvrpHd.col(i) + exp(-wX*dtHT(i))*(rXTH.col(i) - rvrpHd.col(i));
    }

    // dtHT(0) is unused
    // rvrpHd.col(0) is unused
    rvrpTd.col(0) = rCw0/(1 - exp(-wX*dtTH(0))) + rXHT.col(1)/(1 - exp(wX*dtTH(0)));
    // rXHT.col(0) is unused
    rXTH.col(0) = rCw0;

    // double sopport
    // ******************************
    // final
    rXeoDS.col(ht_config.stepNum) = rvrpHd.col(ht_config.stepNum);
    rXiniDS.col(ht_config.stepNum) = rvrpTd.col(ht_config.stepNum-1) + exp(-wX*dtDSini(ht_config.stepNum))*(rXHT.col(ht_config.stepNum) - rvrpTd.col(ht_config.stepNum-1));
    // ******************************
    drXeoDS.col(ht_config.stepNum) = wX*(rXeoDS.col(ht_config.stepNum) - rvrpHd.col(ht_config.stepNum));
    drXiniDS.col(ht_config.stepNum) = wX*(rXiniDS.col(ht_config.stepNum) - rvrpTd.col(ht_config.stepNum-1));

    // ******************************
    ddrXeoDS.col(ht_config.stepNum) = Vector3d::Zero();
    ddrXiniDS.col(ht_config.stepNum) = wX*wX*exp(-wX*dtDSini(ht_config.stepNum))*(rXHT.col(ht_config.stepNum) - rvrpTd.col(ht_config.stepNum-1));

    for(int i=ht_config.stepNum-1; i>0; i--){
      rXeoDS.col(i) = rvrpHd.col(i) + exp(wX*dtDSend(i))*(rXHT.col(i) - rvrpHd.col(i));
      rXiniDS.col(i) = rvrpTd.col(i-1) + exp(-wX*dtDSini(i))*(rXHT.col(i) - rvrpTd.col(i-1));

      drXeoDS.col(i) = wX*(rXeoDS.col(i) - rvrpHd.col(i));
      drXiniDS.col(i) = wX*(rXiniDS.col(i) - rvrpTd.col(i-1));

      ddrXeoDS.col(i) = wX*wX*exp(wX*dtDSend(i))*(rXHT.col(i) - rvrpHd.col(i));
      ddrXiniDS.col(i) = wX*wX*exp(-wX*dtDSini(i))*(rXHT.col(i) - rvrpTd.col(i-1));
    }

    // start
    // ******************************
    // rXeoDS.col(0) is unused
    // rXeoDS.col(0) = rvrpTd.col(0) + exp(wX*dtDSend(0))*(rXTH.col(0) - rvrpTd.col(0));
    rXiniDS.col(0) = rXTH.col(0);// assumption
    // ******************************
    // drXeoDS.col(0) is unused
    // drXeoDS.col(0) = wX*(rXeoDS.col(0) - rvrpTd.col(0));
    drXiniDS.col(0) = Vector3d::Zero();// assumption
    // ******************************
    // ddrXeoDS.col(0) is unused
    // ddrXeoDS.col(0) = wX*wX*exp(wX*dtDSend(0))*(rXTH.col(0) - rvrpTd.col(0));
    ddrXiniDS.col(0) = Vector3d::Zero();// assumption
    // ****************************************************************
  }

  double tf = ht_config.tstab + ht_config.dtstep*(1.-ht_config.alphaHTstep) + ht_config.dtstep*(ht_config.stepNum-1);

  double twalk = t - ht_config.tstab;
  if(round_cast(t, 3)<round_cast(ht_config.tstab, 3)){
    for(int i=0; i<3; i++){
      des = makeSpline5(t-tw0, twf, rXpreDes(i), rXf(i));

      rXDes(i) = des(0) + rX0(i);
      drXDes(i) = des(1);
    }
  }
  else if(round_cast(t, 3)<round_cast(tf, 3)){
    double twDS;

    if(initial_walking){
      tphasef = dtTH(stepPhase) - dtDSini(stepPhase+1);
      // same as dtHT(stepPhase) - dtDSend(stepPhase) + dtTH(stepPhase) - dtDSini(stepPhase+1)

      twDS = twalk - tDS0;
      for(int i=0; i<3; i++){
        des = makeSpline5(twDS, tphasef,
                          rXiniDS.col(stepPhase)(i),
                          drXiniDS.col(stepPhase)(i),
                          ddrXiniDS.col(stepPhase)(i),
                          rXiniDS.col(stepPhase+1)(i),
                          drXiniDS.col(stepPhase+1)(i),
                          ddrXiniDS.col(stepPhase+1)(i));

        rXDes(i) = des(0);
        drXDes(i) = des(1);
      }

      if(round_cast(twDS, 3) == round_cast(tphasef, 3)){
        support = 1;

        tDS0 = twalk;
        stepPhase++;
        initial_walking = false;
      }
    }

    else{
      twDS = twalk - tDS0;

      if(support==0){
        tphasef = dtHT(stepPhase) - dtDSend(stepPhase) + dtTH(stepPhase) - dtDSini(stepPhase+1);

        for(int i=0; i<3; i++){
          des = makeSpline5(twDS, tphasef,
                            rXeoDS.col(stepPhase)(i),
                            drXeoDS.col(stepPhase)(i),
                            ddrXeoDS.col(stepPhase)(i),
                            rXiniDS.col(stepPhase+1)(i),
                            drXiniDS.col(stepPhase+1)(i),
                            ddrXiniDS.col(stepPhase+1)(i));

          rXDes(i) = des(0);
          drXDes(i) = des(1);
        }

        if(round_cast(twDS, 3) == round_cast(tphasef, 3)){
          support = 1;
          tDS0 = twalk;
          stepPhase++;
        }
      }

      else if(support==1){
        tphasef = dtDSini(stepPhase)+dtDSend(stepPhase);

        for(int i=0; i<3; i++){
          des = makeSpline5(twDS, tphasef,
                            rXiniDS.col(stepPhase)(i),
                            drXiniDS.col(stepPhase)(i),
                            ddrXiniDS.col(stepPhase)(i),
                            rXeoDS.col(stepPhase)(i),
                            drXeoDS.col(stepPhase)(i),
                            ddrXeoDS.col(stepPhase)(i));

          rXDes(i) = des(0);
          drXDes(i) = des(1);
        }

        if(round_cast(twDS, 3) == round_cast(tphasef, 3)){
          support = 0;
          tDS0 = twalk;
        }
      }
    }
  }
  else{
    rXDes = rXHT.col(ht_config.stepNum);
    drXDes = wX*(rXDes - rXHT.col(ht_config.stepNum));
  }
}
