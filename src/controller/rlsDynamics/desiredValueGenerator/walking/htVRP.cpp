 /**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"


void RLS::Walking::htVRP(const double &t)
{
  if(debug) DEBUG;

  if(rvrpHd.cols() == 0){
    cout << "Walking desired values not initialized..." << endl;
    gc;

    rCDes = rCw0;
    drCDes = Vector3d::Zero();
    ddrCDes = Vector3d::Zero();

    rXDes = rX0;
    drXDes = Vector3d::Zero();

    return;
  }

  double sinhwX, ewXt;
  MatrixXd Pv;
  MatrixXd tMat0, tMatf;
  Vector3d rvrp;

  double tf = ht_config.tstab + ht_config.dtstep*(ht_config.convergenceNum-1) + tInitial;

  double twalk = t - ht_config.tstab - tInitial;
  double twS = twalk - tDS0;

  if(round_cast(t, 3)<round_cast(ht_config.tstab+tInitial, 3)){
    // Matrix3d desM = makeSpline5(t-tw0, twf, rXpreDes, rXf);
    Matrix3d desM = makeSpline5(t-tw0, twf, rXpreDes, Vector3d::Zero());

    rCDes = RBw0*desM.col(0) + rCw0;
    drCDes = RBw0*desM.col(1);
    ddrCDes = RBw0*desM.col(2);

    rXDes = RBw0*desM.col(0) + rX0;
    drXDes = RBw0*desM.col(1);
  }
  else if(round_cast(t, 3)>round_cast(tf, 3) && round_cast(t, 3)<round_cast(tf+convT, 3)){
    for(int i=0; i<3; i++){
      des = makeSpline5(twalk-tDS0, convT, rCSS.col(vwpNum)(i), rXSS.col(vwpNum)(i));

      rCDes(i) = des(0);
      drCDes(i) = des(1);
      ddrCDes(i) = des(2);
    }

    rXDes = rXSS.col(vwpNum);
    drXDes = Vector3d::Zero();
  }
  else if(stepPhase<ht_config.convergenceNum){
    if(support==0){ ////////////////// SS
      tphasef = dtS(stepPhase);

      //spline
      sinhwX = sinh(wX * twS);
      tMat0 = maketMat(1,ht_config.ipDim*2, 0.);
      tMatf = maketMat(1,ht_config.ipDim*2, twS);
      ewXt = exp(-wX*twS);
      Pv = findPolyParam(0., tphasef, makePosBoundary(ht_config.ipDim, rvrpHd.col(stepPhase), rvrpTd.col(stepPhase)));
      rXDes.transpose() = maketMat(1,ht_config.ipDim*2, twS)*Cp*Pv + exp(wX*twS)*(rXSS.col(stepPhase).transpose() - maketMat(1,ht_config.ipDim*2, 0.)*Cp*Pv);
      rCDes.transpose() = ewXt*rCSS.col(stepPhase).transpose() + sinhwX*rXSS.col(stepPhase).transpose() + ((tMatf - ewXt*tMat0)*Cm - sinhwX*tMat0)*Cp*Pv;
      rvrp.transpose() = maketMat(1,ht_config.ipDim*2, twS)*Pv;

      if(round_cast(twS, 3) == round_cast(tphasef, 3)){
        support = 1;
        tDS0 = twalk;

        stepPhase++;
      }
    }
    else if(support==1){ ////////////////// DS
      tphasef = dtD(stepPhase);

      //spline
      sinhwX = sinh(wX * twS);
      tMat0 = maketMat(1,ht_config.ipDim*2, 0.);
      tMatf = maketMat(1,ht_config.ipDim*2, twS);
      ewXt = exp(-wX*twS);
      Pv = findPolyParam(0., tphasef, makePosBoundary(ht_config.ipDim, rvrpTd.col(stepPhase-1), rvrpHd.col(stepPhase)));
      rXDes.transpose() = maketMat(1,ht_config.ipDim*2, twS)*Cp*Pv + exp(wX*twS)*(rXDS.col(stepPhase).transpose() - maketMat(1,ht_config.ipDim*2, 0.)*Cp*Pv);
      rCDes.transpose() = ewXt*rCDS.col(stepPhase).transpose() + sinhwX*rXDS.col(stepPhase).transpose() + ((tMatf - ewXt*tMat0)*Cm - sinhwX*tMat0)*Cp*Pv;
      rvrp.transpose() = maketMat(1,ht_config.ipDim*2, twS) * Pv;

      if(round_cast(twS, 3) == round_cast(tphasef, 3)){
        support = 0;
        tDS0 = twalk;
      }
    }

    drCDes = wX*(rXDes - rCDes);
    ddrCDes = wX*wX*(rCDes - rvrp);

    drXDes = wX*(rXDes - rvrp);

  }
  else {
    rCDes = rXSS.col(vwpNum);
    rXDes = rXSS.col(vwpNum);

    drCDes = Vector3d::Zero();
    ddrCDes = Vector3d::Zero();
    drXDes = Vector3d::Zero();
  }
}
