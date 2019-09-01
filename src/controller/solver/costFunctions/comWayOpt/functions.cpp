#include "config.hpp"
#include "common.hpp"

#include "walkingFunction.hpp"
#include "comWayOpt.hpp"


MatrixXd RLS::comWayOpt::calcDwp(VectorXd T)
{
  if(CWO_DEBUG) DEBUG;
  // cout << "calcDwp" << endl;

  MatrixXd dwp = MatrixXd::Zero(3, rCnum);

  dwp.col(Tnum) = vwp.col(Tnum); // last position
  dwp.col(0) = vwp.col(0); // first position

  // backward calculation of DCM
  MatrixXd Pv;
  for(int i=Tnum-1; i>1; i--){
    Pv = wf.findPolyParam(0., T(i), wf.makePosBoundary(ipDim, vwp.col(i), vwp.col(i+1)));
    dwp.col(i).transpose() = wf.maketMat(1,ipDim*2, 0.)*Cp*Pv + exp(-wX*T(i))*(dwp.col(i+1).transpose() - wf.maketMat(1,ipDim*2, T(i))*Cp*Pv);
  }

  // calculate vwp(1) **********
  // make Pv
  MatrixXd pfD = wf.findPolyParam(0., T(1), wf.makePosBoundary(ipDim, 0., 1.));
  MatrixXd pfS = wf.findPolyParam(0., T(0), wf.makePosBoundary(ipDim, 0., 1.));
  VectorXd zerone = VectorXd::Zero(ipDim*2);
  zerone(0) = 1.;
  VectorXd p0D = zerone - pfD, p1D = pfD;
  VectorXd p0S = zerone - pfS, p1S = pfS;

  // make c matrix
  MatrixXd c0_TD = (wf.maketMat(1,ipDim*2, 0.) - exp(-wX*T(1))*wf.maketMat(1,ipDim*2, T(1))) * Cp;
  MatrixXd cTS_0 = (wf.maketMat(1,ipDim*2, T(0)) - exp(wX*T(0))*wf.maketMat(1,ipDim*2, 0.)) * Cp;

  // calculate
  MatrixXd c_X = c0_TD*p0D - cTS_0*p1S;
  // warning vwp(1) rewrite
  vwp.col(1).transpose() = (exp(wX*T(0))*dwp.col(0).transpose() - exp(-wX*T(1))*dwp.col(2).transpose() + cTS_0*p0S*vwp.col(0).transpose() - c0_TD*p1D*vwp.col(2).transpose()) / c_X(0,0);
  // ******************************

  // dwp(1)
  Pv = wf.findPolyParam(0., T(1), wf.makePosBoundary(ipDim, vwp.col(1), vwp.col(2)));
  dwp.col(1).transpose() = wf.maketMat(1,ipDim*2, 0.)*Cp*Pv + exp(-wX*T(1))*(dwp.col(2).transpose() - wf.maketMat(1,ipDim*2, T(1))*Cp*Pv);

  return dwp;
}

MatrixXd RLS::comWayOpt::calcCwp(VectorXd T, MatrixXd dwp)
{
  if(CWO_DEBUG) DEBUG;
  // cout << "calcCwp" << endl;

  MatrixXd cwp = MatrixXd::Zero(3, rCnum);

  cwp.col(0) = vwp.col(0); // first position

  // forward calculation of CoM
  double sinhwX, ewXt;
  MatrixXd tMat0, tMatf;
  MatrixXd Pv;
  for(int i=0; i<Tnum; i++){ //mod
    sinhwX = sinh(wX * T(i));
    tMat0 = wf.maketMat(1,ipDim*2, 0.);
    tMatf = wf.maketMat(1,ipDim*2, T(i));
    ewXt = exp(-wX*T(i));
    Pv = wf.findPolyParam(0., T(i), wf.makePosBoundary(ipDim, vwp.col(i), vwp.col(i+1)));
    cwp.col(i+1).transpose() = ewXt*cwp.col(i).transpose() + sinhwX*dwp.col(i).transpose() + ((tMatf - ewXt*tMat0)*Cm - sinhwX*tMat0)*Cp*Pv;
  }

  // VectorXd comWayOpt = VectorXd::Zero(3*rCnum);
  // for(int i=0; i<rCnum; i++)
  //   comWayOpt.segmnet(i*3, 3) = cwp.col(i);

  return cwp;
}

// for gradient

// dTnDwp(i)はdwp(i)をT(num)で微分したもの
MatrixXd RLS::comWayOpt::calcdTnDwp(int num, VectorXd T, MatrixXd dwp)
{
  if(CWO_DEBUG) DEBUG;
  // cout << "calcdTnDwp" << endl;

  MatrixXd dTnDwp = MatrixXd::Zero(3,rCnum);

  if(num==0){
    MatrixXd pfT1 = wf.findPolyParam(0., T(1), wf.makePosBoundary(ipDim, 0., 1.));
    MatrixXd pfT0 = wf.findPolyParam(0., T(0), wf.makePosBoundary(ipDim, 0., 1.));
    MatrixXd dT1pfT1 = wf.finddPolyParam(0., T(1), wf.makePosBoundary(ipDim, 0., 1.));
    MatrixXd dT0pfT0 = wf.finddPolyParam(0., T(0), wf.makePosBoundary(ipDim, 0., 1.));
    VectorXd zerone = VectorXd::Zero(ipDim*2);
    zerone(0) = 1.;
    VectorXd p0T1 = zerone - pfT1, p1T1 = pfT1;
    VectorXd p0T0 = zerone - pfT0, p1T0 = pfT0;
    VectorXd dT1p0T1 = -dT1pfT1, dT1p1T1 = dT1pfT1;
    VectorXd dT0p0T0 = -dT0pfT0, dT0p1T0 = dT0pfT0;

    double expwXT0 = exp(wX*T(0)), expwXT1 = exp(-wX*T(1));
    MatrixXd cT1 = (wf.maketMat(1,ipDim*2, 0.) - expwXT1*wf.maketMat(1,ipDim*2, T(1))) * Cp;
    MatrixXd cT0 = (wf.maketMat(1,ipDim*2, T(0)) - expwXT0*wf.maketMat(1,ipDim*2, 0.)) * Cp;
    // MatrixXd dT1cT1 = (wX*expwXT1*wf.maketMat(1,ipDim*2, T(1)) - expwXT1*wf.maketMat(1,ipDim*2, T(1))) * Cp;
    MatrixXd dT0cT0 = (wf.makedtMat(1,ipDim*2, T(0)) - wX*expwXT0*wf.maketMat(1,ipDim*2, 0.)) * Cp;

    MatrixXd c_X = cT1*p0T1 - cT0*p1T0;
    VectorXd dT0rvrp1 = ( (wX*expwXT0*dwp.col(0).transpose() + (dT0cT0*p0T1+cT1*dT1p0T1)*vwp.col(1).transpose() + (dT0cT0*p0T0+cT0*dT0p0T0)*vwp.col(0).transpose()) / c_X(0,0) ).transpose();

    dTnDwp.col(1).transpose() = (wf.maketMat(1, ipDim*2, 0) - wf.maketMat(1, ipDim*2, T(1)))*Cp*(p0T1*dT0rvrp1.transpose());
  }
  else{
    for(int i=num; i>0; i--){
      if(i==num){
        if(num==1){
          MatrixXd pfT1 = wf.findPolyParam(0., T(1), wf.makePosBoundary(ipDim, 0., 1.));
          MatrixXd pfT0 = wf.findPolyParam(0., T(0), wf.makePosBoundary(ipDim, 0., 1.));
          MatrixXd dT1pfT1 = wf.finddPolyParam(0., T(1), wf.makePosBoundary(ipDim, 0., 1.));
          MatrixXd dT0pfT0 = wf.finddPolyParam(0., T(0), wf.makePosBoundary(ipDim, 0., 1.));
          VectorXd zerone = VectorXd::Zero(ipDim*2);
          zerone(0) = 1.;
          VectorXd p0T1 = zerone - pfT1, p1T1 = pfT1;
          VectorXd p0T0 = zerone - pfT0, p1T0 = pfT0;
          VectorXd dT1p0T1 = -dT1pfT1, dT1p1T1 = dT1pfT1;
          VectorXd dT0p0T0 = -dT0pfT0, dT0p1T0 = dT0pfT0;
          // make c matrix
          double expwXT0 = exp(wX*T(0)), expwXT1 = exp(-wX*T(1));
          MatrixXd cT1 = (wf.maketMat(1,ipDim*2, 0.) - expwXT1*wf.maketMat(1,ipDim*2, T(1))) * Cp;
          MatrixXd cT0 = (wf.maketMat(1,ipDim*2, T(0)) - expwXT0*wf.maketMat(1,ipDim*2, 0.)) * Cp;
          MatrixXd dT1cT1 = (wX*expwXT1*wf.maketMat(1,ipDim*2, T(1)) - expwXT1*wf.maketMat(1,ipDim*2, T(1))) * Cp;
          // MatrixXd dT0cT0 = (wf.makedtMat(1,ipDim*2, T(0)) - wX*expwXT0*wf.maketMat(1,ipDim*2, 0.)) * Cp;

          MatrixXd c_X = cT1*p0T1 - cT0*p1T0;
          VectorXd dT1rvrp1 = ( (wX*expwXT1*dwp.col(2).transpose() - (dT1cT1*p0T1+cT1*dT1p0T1)*vwp.col(1).transpose() + (dT1cT1*p1T1+cT1*dT1p1T1)*vwp.col(2).transpose()) / c_X(0,0) ).transpose();
          // calculate
          dTnDwp.col(i).transpose() = -wX*expwXT1*dwp.col(2).transpose() - wf.makedtMat(1,ipDim*2,T(1))*Cp* (p0T1*vwp.col(1).transpose()+p1T1*vwp.col(2).transpose())\
           + (wf.maketMat(1,ipDim*2, 0.)-wf.maketMat(1,ipDim*2, T(1)))*Cp*(dT1pfT1*vwp.col(1).transpose() + p0T1*dT1rvrp1.transpose() + dT1p1T1*vwp.col(2).transpose());
        }
        else{
          MatrixXd Pv = wf.findPolyParam(0., T(i), wf.makePosBoundary(ipDim, vwp.col(i), vwp.col(i+1)));
          MatrixXd dPv = wf.finddPolyParam(0., T(i), wf.makePosBoundary(ipDim, vwp.col(i), vwp.col(i+1)));
          dTnDwp.col(i).transpose() = wf.maketMat(1,ipDim*2, 0.)*Cp*dPv - wX * exp(-wX*T(i))*(dwp.col(i+1).transpose()\
          - wf.maketMat(1,ipDim*2, T(i))*Cp*Pv) + exp(-wX*T(i))*(-wf.makedtMat(1,ipDim*2, T(i))*Cp*Pv - wf.maketMat(1,ipDim*2, T(i))*Cp*dPv);
        }
      }
      else{
        dTnDwp.col(i) = exp(-wX*T(i)) * dTnDwp.col(i+1);
      }
    }
  }

  return dTnDwp;
}

// dTnCwp(i)はcwp(i+1)をT(num)で微分したもの
MatrixXd RLS::comWayOpt::calcdTnCwp(int num, VectorXd T, MatrixXd cwp, MatrixXd dwp, MatrixXd dTnDwp)
{
  if(CWO_DEBUG) DEBUG;
  // cout << "calcdTnCwp" << endl;

  MatrixXd dTnCwp = MatrixXd::Zero(3,rCnum);

  double sinhwX, ewXt, wXcoshwX;
  MatrixXd tMat0, dtMat0, tMatf, dtMatf;
  MatrixXd Pv, dPv;

  VectorXd dT0rvrp1, dT1rvrp1;
  VectorXd p0T1, p1T1;
  VectorXd p0T0, p1T0;
  VectorXd dT1p0T1, dT1p1T1;
  VectorXd dT0p0T0, dT0p1T0;
  if(num<2){
    MatrixXd pfT1 = wf.findPolyParam(0., T(1), wf.makePosBoundary(ipDim, 0., 1.));
    MatrixXd pfT0 = wf.findPolyParam(0., T(0), wf.makePosBoundary(ipDim, 0., 1.));
    MatrixXd dT1pfT1 = wf.finddPolyParam(0., T(1), wf.makePosBoundary(ipDim, 0., 1.));
    MatrixXd dT0pfT0 = wf.finddPolyParam(0., T(0), wf.makePosBoundary(ipDim, 0., 1.));
    VectorXd zerone = VectorXd::Zero(ipDim*2);
    zerone(0) = 1.;
    p0T1 = zerone - pfT1; p1T1 = pfT1;
    p0T0 = zerone - pfT0; p1T0 = pfT0;
    dT1p0T1 = -dT1pfT1; dT1p1T1 = dT1pfT1;
    dT0p0T0 = -dT0pfT0; dT0p1T0 = dT0pfT0;

    double expwXT0 = exp(wX*T(0)), expwXT1 = exp(-wX*T(1));
    MatrixXd cT1 = (wf.maketMat(1,ipDim*2, 0.) - expwXT1*wf.maketMat(1,ipDim*2, T(1))) * Cp;
    MatrixXd cT0 = (wf.maketMat(1,ipDim*2, T(0)) - expwXT0*wf.maketMat(1,ipDim*2, 0.)) * Cp;
    MatrixXd dT1cT1 = (wX*expwXT1*wf.maketMat(1,ipDim*2, T(1)) - expwXT1*wf.maketMat(1,ipDim*2, T(1))) * Cp;
    MatrixXd dT0cT0 = (wf.makedtMat(1,ipDim*2, T(0)) - wX*expwXT0*wf.maketMat(1,ipDim*2, 0.)) * Cp;

    MatrixXd c_X = cT1*p0T1 - cT0*p1T0;
    dT0rvrp1 = ( (wX*expwXT0*dwp.col(0).transpose() + (dT0cT0*p0T1+cT1*dT1p0T1)*vwp.col(1).transpose() + (dT0cT0*p0T0+cT0*dT0p0T0)*vwp.col(0).transpose()) / c_X(0,0) ).transpose();
    dT1rvrp1 = ( (wX*expwXT1*dwp.col(2).transpose() - (dT1cT1*p0T1+cT1*dT1p0T1)*vwp.col(1).transpose() + (dT1cT1*p1T1+cT1*dT1p1T1)*vwp.col(2).transpose()) / c_X(0,0) ).transpose();
  }

  for(int i=1; i<rCnum; i++){ //mod
    if(i <= num){
      ewXt = exp(-wX*T(i-1));
      sinhwX = sinh(wX*T(i-1));
      dTnCwp.col(i) = ewXt*dTnCwp.col(i-1) + sinhwX*dTnDwp.col(i-1);
      if(i==1 && num==1){ // d/dT1 rC^1
        tMat0 = wf.maketMat(1,ipDim*2, 0.);
        tMatf = wf.maketMat(1,ipDim*2, T(0));
        // dTnCwp.col(i).transpose() += ((tMatf - ewXt*tMat0)*Cm - sinhwX*tMat0)*Cp*(p1T0*dT1rvrp1.transpose()); // 結局前の項0だし．．．
        dTnCwp.col(i).transpose() = ((tMatf - ewXt*tMat0)*Cm - sinhwX*tMat0)*Cp*(p1T0*dT1rvrp1.transpose());
      }
    }
    else if(i == num+1){
      ewXt = exp(-wX*T(i-1));
      sinhwX = sinh(wX * T(i-1));
      wXcoshwX = wX*cosh(wX * T(i-1));
      tMat0 = wf.maketMat(1,ipDim*2, 0.);
      // dtMat0 = wf.makedtMat(1,ipDim*2, 0.);
      dtMat0 = MatrixXd::Zero(1, ipDim*2);
      tMatf = wf.maketMat(1,ipDim*2, T(i-1));
      dtMatf = wf.makedtMat(1,ipDim*2, T(i-1));
      Pv = wf.findPolyParam(0., T(i-1), wf.makePosBoundary(ipDim, vwp.col(i-1), vwp.col(i)));

      if(i==1) // d/dT0 rC^1
        dPv = dT0p0T0*vwp.col(0).transpose() + dT0p1T0*vwp.col(1).transpose() + p1T0*dT0rvrp1.transpose();
      else if(i==2) // d/dT1 rC^2
        dPv = dT1p0T1*vwp.col(1).transpose() + p0T1*dT1rvrp1.transpose() + dT1p1T1*vwp.col(2).transpose();
      else
        dPv = wf.finddPolyParam(0., T(i-1), wf.makePosBoundary(ipDim, vwp.col(i-1), vwp.col(i)));

      dTnCwp.col(i).transpose() = -wX*ewXt*cwp.col(i-1).transpose() + ewXt*dTnCwp.col(i-1).transpose()\
        + wXcoshwX*dwp.col(i-1).transpose() + sinhwX*dTnDwp.col(i-1).transpose()\
        +((dtMatf + wX*ewXt*tMat0)*Cm - wXcoshwX*tMat0)*Cp*Pv + ((tMatf - ewXt*tMat0)*Cm - sinhwX*tMat0)*Cp*dPv;
    }
    else{ // i > num+1
      dTnCwp.col(i) = exp(-wX*T(i-1)) * dTnCwp.col(i-1);
    }
  }

  return dTnCwp;
}
