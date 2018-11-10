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
    rXHTBar.col(ht_config.stepNum) = rf.col(ht_config.stepNum) + Dzvrp - rHextDes;

    // final desired VRP
    // rvrpTd.col(ht_config.stepNum) is unused
    rvrpHdBar.col(ht_config.stepNum) = rXHTBar.col(ht_config.stepNum);

    for(int i=ht_config.stepNum-1; i>0; i--){
      if(i==ht_config.stepNum-1){
        rvrpTd.col(i) = rf.col(i) + Dzvrp;
        rvrpHd.col(i) = rf.col(i) + Dzvrp;
      }
      else if(i==ht_config.stepNum-2){
        rvrpTd.col(i) = rf.col(i) + Dzvrp;
        rvrpHd.col(i) = rf.col(i) + heelOffset + Dzvrp;
      }
      else if(i==1){
        rvrpTd.col(i) = rf.col(i) + toeOffset + Dzvrp;
        rvrpHd.col(i) = rf.col(i) + Dzvrp;
      }
      else{
        rvrpTd.col(i) = rf.col(i) + toeOffset + Dzvrp;
        rvrpHd.col(i) = rf.col(i) + heelOffset + Dzvrp;
      }

      rvrpTdBar.col(i) = rvrpTd.col(i) - rHextDes;
      rvrpHdBar.col(i) = rvrpHd.col(i) - rHextDes;

      rXTHBar.col(i) = rvrpTdBar.col(i) + exp(-wX*dtTH(i))*(rXHTBar.col(i+1) - rvrpTdBar.col(i));
      rXHTBar.col(i) = rvrpHdBar.col(i) + exp(-wX*dtHT(i))*(rXTHBar.col(i) - rvrpHdBar.col(i));
    }

    rvrpTd.col(0) = rCw0/(1 - exp(-wX*dtTH(0))) + rXHT.col(1)/(1 - exp(wX*dtTH(0)));
    rXTH.col(0) = rCw0;

    // dtHT(0) is unused
    // rvrpHd.col(0) is unused
    rvrpTdBar.col(0) = rCw0/(1 - exp(-wX*dtTH(0))) + rXHTBar.col(1)/(1 - exp(wX*dtTH(0)));

    // rXHT.col(0) is unused
    rXTHBar.col(0) = rCw0;

    // double sopport
    // ******************************
    // final
    rXeoDSBar.col(ht_config.stepNum) = rvrpHdBar.col(ht_config.stepNum);
    rXiniDSBar.col(ht_config.stepNum) = rvrpTdBar.col(ht_config.stepNum-1) + exp(-wX*dtDSini(ht_config.stepNum))*(rXHTBar.col(ht_config.stepNum) - rvrpTdBar.col(ht_config.stepNum-1));
    // ******************************
    drXeoDSBar.col(ht_config.stepNum) = wX*(rXeoDSBar.col(ht_config.stepNum) - rvrpHdBar.col(ht_config.stepNum));
    drXiniDSBar.col(ht_config.stepNum) = wX*(rXiniDSBar.col(ht_config.stepNum) - rvrpTdBar.col(ht_config.stepNum-1));

    // ******************************
    ddrXeoDSBar.col(ht_config.stepNum) = Vector3d::Zero();
    ddrXiniDSBar.col(ht_config.stepNum) = wX*wX*exp(-wX*dtDSini(ht_config.stepNum))*(rXHTBar.col(ht_config.stepNum) - rvrpTdBar.col(ht_config.stepNum-1));

    for(int i=ht_config.stepNum-1; i>0; i--){
      rXeoDSBar.col(i) = rvrpHdBar.col(i) + exp(wX*dtDSend(i))*(rXHTBar.col(i) - rvrpHdBar.col(i));
      rXiniDSBar.col(i) = rvrpTdBar.col(i-1) + exp(-wX*dtDSini(i))*(rXHTBar.col(i) - rvrpTdBar.col(i-1));

      drXeoDSBar.col(i) = wX*(rXeoDSBar.col(i) - rvrpHdBar.col(i));
      drXiniDSBar.col(i) = wX*(rXiniDSBar.col(i) - rvrpTdBar.col(i-1));

      ddrXeoDSBar.col(i) = wX*wX*exp(wX*dtDSend(i))*(rXHTBar.col(i) - rvrpHdBar.col(i));
      ddrXiniDSBar.col(i) = wX*wX*exp(-wX*dtDSini(i))*(rXHTBar.col(i) - rvrpTdBar.col(i-1));
    }

    // start
    // ******************************
    // rXeoDS.col(0) is unused
    // rXeoDS.col(0) = rvrpTd.col(0) + exp(wX*dtDSend(0))*(rXTH.col(0) - rvrpTd.col(0));
    rXiniDSBar.col(0) = rXTH.col(0);// assumption
    // ******************************
    // drXeoDS.col(0) is unused
    // drXeoDS.col(0) = wX*(rXeoDS.col(0) - rvrpTd.col(0));
    drXiniDSBar.col(0) = Vector3d::Zero();// assumption
    // ******************************
    // ddrXeoDS.col(0) is unused
    // ddrXeoDS.col(0) = wX*wX*exp(wX*dtDSend(0))*(rXTH.col(0) - rvrpTd.col(0));
    ddrXiniDSBar.col(0) = Vector3d::Zero();// assumption
    // ****************************************************************
  }

  double tf = ht_config.tstab + ht_config.dtstep*(1.-ht_config.alphaHTstep) + ht_config.dtstep*(ht_config.stepNum-1);

  double twalk = t - ht_config.tstab;
  if(round_cast(t, 3)<round_cast(ht_config.tstab, 3)){
    for(int i=0; i<3; i++){
      des = makeSpline5(t-tw0, twf, rXpreDes(i), rXf(i));

      rXBarDes(i) = des(0) + rX0(i);
      drXBarDes(i) = des(1);
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
                          rXiniDSBar.col(stepPhase)(i),
                          drXiniDSBar.col(stepPhase)(i),
                          ddrXiniDSBar.col(stepPhase)(i),
                          rXiniDSBar.col(stepPhase+1)(i),
                          drXiniDSBar.col(stepPhase+1)(i),
                          ddrXiniDSBar.col(stepPhase+1)(i));

        rXBarDes(i) = des(0);
        drXBarDes(i) = des(1);
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
                            rXeoDSBar.col(stepPhase)(i),
                            drXeoDSBar.col(stepPhase)(i),
                            ddrXeoDSBar.col(stepPhase)(i),
                            rXiniDSBar.col(stepPhase+1)(i),
                            drXiniDSBar.col(stepPhase+1)(i),
                            ddrXiniDSBar.col(stepPhase+1)(i));

          rXBarDes(i) = des(0);
          drXBarDes(i) = des(1);
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
                            rXiniDSBar.col(stepPhase)(i),
                            drXiniDSBar.col(stepPhase)(i),
                            ddrXiniDSBar.col(stepPhase)(i),
                            rXeoDSBar.col(stepPhase)(i),
                            drXeoDSBar.col(stepPhase)(i),
                            ddrXeoDSBar.col(stepPhase)(i));

          rXBarDes(i) = des(0);
          drXBarDes(i) = des(1);
        }

        if(round_cast(twDS, 3) == round_cast(tphasef, 3)){
          support = 0;
          tDS0 = twalk;
        }
      }
    }
  }
  else{
    rXBarDes = rXHTBar.col(ht_config.stepNum);
    drXBarDes = wX*(rXBarDes - rXHTBar.col(ht_config.stepNum));
  }
}
