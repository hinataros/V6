 /**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::extht(const double &t)
{
  if(debug) DEBUG;

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
    // DCM dynamics based exponential interpolation
    // // toe to heel
    // // ******************************
    // if(round_cast(twalk, 3)<500){
    //   rXBarDes = rvrpTd.col(i) +
    //     exp(wX*(tstep-dtTH(i)))*(rXHT.col(i+1) - rvrpTd.col(i));

    //   drXBarDes = wX*(rXBarDes - rvrpTd.col(i));
    // }

    // // heel to toe
    // // ******************************
    // else if(round_cast(twalk, 3)<500+500){
    //   rXBarDes = rvrpHd.col(i) +
    //     exp(wX*(tstep-dtHT(i)))*(rXTH.col(i) - rvrpHd.col(i));

    //   drXBarDes = wX*(rXBarDes - rvrpHd.col(i));
    // }

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
