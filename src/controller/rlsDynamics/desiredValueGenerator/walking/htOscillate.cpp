 /**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::htOscillate(const double &t)
{
  if(debug) DEBUG;

  double tf = ht_config.tstab + ht_config.dtstep*(1.-ht_config.alphaHTstep) + ht_config.dtstep*(ht_config.convergenceNum-1);

  double twalk = t - ht_config.tstab;
  if(round_cast(t, 3)<round_cast(ht_config.tstab, 3)){
    for(int i=0; i<3; i++){
      des = makeSpline5(t-tw0, twf, rXpreDes(i), rXf(i));

      rXDes(i) = des(0) + rX0(i);
      drXDes(i) = des(1);
    }
  }
  else if(round_cast(t, 3)<round_cast(tf, 3)){
    // DCM dynamics based exponential interpolation
    // // toe to heel
    // // ******************************
    // if(round_cast(twalk, 3)<500){
    //   rXDes = rvrpTd.col(i) +
    //     exp(wX*(tstep-dtTH(i)))*(rXHT.col(i+1) - rvrpTd.col(i));

    //   drXDes = wX*(rXDes - rvrpTd.col(i));
    // }

    // // heel to toe
    // // ******************************
    // else if(round_cast(twalk, 3)<500+500){
    //   rXDes = rvrpHd.col(i) +
    //     exp(wX*(tstep-dtHT(i)))*(rXTH.col(i) - rvrpHd.col(i));

    //   drXDes = wX*(rXDes - rvrpHd.col(i));
    // }

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
          if(i==2 && (stepPhase > 1 && stepPhase<(ht_config.convergenceNum-1))) {
            double cur=0.;
            double init, end;
            if(twDS < (tphasef/2.)){
              cur = twDS;
              init = rXeoDS.col(stepPhase)(i);
              end = rXeoDS.col(stepPhase)(i) + ht_config.zOsc;
            } else  {
              cur = twDS-tphasef/2.;
              init = rXeoDS.col(stepPhase)(i) + ht_config.zOsc;
              end = rXiniDS.col(stepPhase+1)(i);
            }
            des = makeSpline5(cur, tphasef/2., init, 0., 0., end, 0., 0.);
          }

          rXDes(i) = des(0);
          drXDes(i) = des(1);
        }

        if(round_cast(twDS, 3) == round_cast(tphasef, 3)){
          support = 1;
          tDS0 = twalk;
          // if(stepPhase<(dtHT.rows()-1))  // amiyata
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
    rXDes = rXHT.col(ht_config.convergenceNum);
    drXDes = wX*(rXDes - rXHT.col(ht_config.convergenceNum));
  }
}
