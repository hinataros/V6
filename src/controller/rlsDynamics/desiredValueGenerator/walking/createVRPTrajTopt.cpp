/**
   @author Sho Miyahara 2018
*/
#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"


void RLS::Walking::createVRPTrajTopt()
{
  if(debug) DEBUG;

  double sinhwX, ewXt;
  MatrixXd tMat0, tMatf;
  MatrixXd Pv;

  // T optim ****************************************
  dT = VectorXd::Zero(vwpNum*2);

  MatrixXd vrpTH = MatrixXd::Zero(3, vwpNum*2+1);
  for(int i=0; i<vwpNum; i++){
    vrpTH.col(i*2) = rvrpHd.col(i);
    vrpTH.col(i*2+1) = rvrpTd.col(i);
  }
  vrpTH.col(vwpNum*2) = rvrpTd.col(vwpNum);

  MatrixXd cwpDes = MatrixXd::Zero(3, vwpNum);
  for(int i=0; i<vwpNum; i++)
    cwpDes.col(i) = (vwpOpt.col(i) + vwpOpt.col(i+1)) / 2.;

  // so(dT);
  // o(rvrpHd);
  // o(rvrpTd);
  // o(vrpTH);
  // o(vwpOpt);
  // o(cwpDes);
  CFSQP::solver(vrpTH, cwpDes, ht_config.ipDim, wX, 0.2, dT);

  for(int i=0; i<vwpNum; i++){
    dtS(i) = dT(i*2);
    dtD(i+1) = dT(i*2+1);
  }
  dtS(vwpNum) = dtD(vwpNum); // 同期ズレで飛ぶ

  Topt = VectorXd::Zero(vwpNum*2 + 1);
  Topt <<
    0., // tstab
    dT;
  // ************************************************

  Cp = makeCMat(ht_config.ipDim*2, 1./wX);
  Cm = makeCMat(ht_config.ipDim*2, -1./wX);

  // final desired DCM position
  rXSS.col(vwpNum) = rvrpHd.col(vwpNum);

  // backward calculation of DCM
  for(int i=vwpNum; i>0; i--){
    if(i!=vwpNum){ // rXSS(vwpNum) is already assumed
      Pv = findPolyParam(0., dtS(i), makePosBoundary(ht_config.ipDim, rvrpHd.col(i), rvrpTd.col(i)));
      rXSS.col(i).transpose() = maketMat(1,ht_config.ipDim*2, 0.)*Cp*Pv + exp(-wX*dtS(i))*(rXDS.col(i+1).transpose() - maketMat(1,ht_config.ipDim*2, dtS(i))*Cp*Pv);
    }
    if(i!=1){
      Pv = findPolyParam(0., dtD(i), makePosBoundary(ht_config.ipDim, rvrpTd.col(i-1), rvrpHd.col(i)));
      rXDS.col(i).transpose() = maketMat(1,ht_config.ipDim*2, 0.)*Cp*Pv + exp(-wX*dtD(i))*(rXSS.col(i).transpose() - maketMat(1,ht_config.ipDim*2, dtD(i))*Cp*Pv);
    }
  }

  rXSS.col(0) = rCSS.col(0) = rvrpHd.col(0);

  // calculate rvrpTd(0) **********
  // make Pv
  MatrixXd pfD = findPolyParam(0., dtD(1), makePosBoundary(ht_config.ipDim, 0., 1.));
  MatrixXd pfS = findPolyParam(0., dtS(0), makePosBoundary(ht_config.ipDim, 0., 1.));
  VectorXd zerone = VectorXd::Zero(ht_config.ipDim*2);
  zerone(0) = 1.;
  VectorXd p0D = zerone - pfD, p1D = pfD;
  VectorXd p0S = zerone - pfS, p1S = pfS;

  // make c matrix
  MatrixXd c0_TD = (maketMat(1,ht_config.ipDim*2, 0.) - exp(-wX*dtD(1))*maketMat(1,ht_config.ipDim*2, dtD(1))) * Cp;
  MatrixXd cTS_0 = (maketMat(1,ht_config.ipDim*2, dtS(0)) - exp(wX*dtS(0))*maketMat(1,ht_config.ipDim*2, 0.)) * Cp;

  // calculate
  MatrixXd c_X = c0_TD*p0D - cTS_0*p1S;
  rvrpTd.col(0).transpose() = (exp(wX*dtS(0))*rXSS.col(0).transpose() - exp(-wX*dtD(1))*rXSS.col(1).transpose()\
    + cTS_0*p0S*rvrpHd.col(0).transpose() - c0_TD*p1D*rvrpHd.col(1).transpose()) / c_X(0,0);
  // o(rvrpTd.col(0));
  // ******************************

  // rXDS(1)
  Pv = findPolyParam(0., dtD(1), makePosBoundary(ht_config.ipDim, rvrpTd.col(0), rvrpHd.col(1)));
  rXDS.col(1).transpose() = maketMat(1,ht_config.ipDim*2, 0.)*Cp*Pv + exp(-wX*dtD(1))*(rXSS.col(1).transpose() - maketMat(1,ht_config.ipDim*2, dtD(1))*Cp*Pv);
  // rXDS(0) is unused

  // forward calculation of CoM
  for(int i=0; i<ht_config.convergenceNum; i++){ //mod
    if(i != 0){
      sinhwX = sinh(wX * dtD(i));
      tMat0 = maketMat(1,ht_config.ipDim*2, 0.);
      tMatf = maketMat(1,ht_config.ipDim*2, dtD(i));
      ewXt = exp(-wX*dtD(i));
      Pv = findPolyParam(0., dtD(i), makePosBoundary(ht_config.ipDim, rvrpTd.col(i-1), rvrpHd.col(i)));
      rCSS.col(i).transpose() = ewXt*rCDS.col(i).transpose() + sinhwX*rXDS.col(i).transpose() + ((tMatf - ewXt*tMat0)*Cm - sinhwX*tMat0)*Cp*Pv;
    }

    if(i!=vwpNum){
      sinhwX = sinh(wX * dtS(i));
      tMat0 = maketMat(1,ht_config.ipDim*2, 0.);
      tMatf = maketMat(1,ht_config.ipDim*2, dtS(i));
      ewXt = exp(-wX*dtS(i));
      Pv = findPolyParam(0., dtS(i), makePosBoundary(ht_config.ipDim, rvrpHd.col(i), rvrpTd.col(i)));
      rCDS.col(i+1).transpose() = ewXt*rCSS.col(i).transpose() + sinhwX*rXSS.col(i).transpose() + ((tMatf - ewXt*tMat0)*Cm - sinhwX*tMat0)*Cp*Pv;
    }
  }
  // rCDS(0) is unused
  convT = (1./wX)*log((rCSS.col(vwpNum)(0)-rXSS.col(vwpNum)(0)) / (sign(rCSS.col(vwpNum)(0)-rXSS.col(vwpNum)(0))*1.e-4));

  // output
  ofstream chC("/usr/local/etc/rls/user/1000/rlsSimulator/sl/result/cmp/dat/ind/chC.dat");
  ofstream chF("/usr/local/etc/rls/user/1000/rlsSimulator/sl/result/cmp/dat/ind/chF.dat");
  ofstream chFS("/usr/local/etc/rls/user/1000/rlsSimulator/sl/result/cmp/dat/ind/chFS.dat");
  ofstream chFD("/usr/local/etc/rls/user/1000/rlsSimulator/sl/result/cmp/dat/ind/chFD.dat");

  for(int i=0; i<vwpNum; i++)
    chC << cwpDes.col(i).head(2).transpose() << endl;
  for(int i=0; i<ht_config.convergenceNum; i++){
    if(i==0)
      chF << rXSS.col(i).head(2).transpose() << endl;
    if(i==vwpNum)
      chF << rXDS.col(i).head(2).transpose() << endl;
    else
      chF << rXDS.col(i).head(2).transpose() << endl << rXSS.col(i).head(2).transpose() << endl;
  }
  for(int i=0; i<ht_config.convergenceNum; i++){
    if(i!=0)
      chFD << rXDS.col(i).head(2).transpose() << endl;
    if(i!=vwpNum)
      chFS << rXSS.col(i).head(2).transpose() << endl;
  }

  chC.close();
  chF.close();
  chFS.close();
  chFD.close();

  // o(rvrpHd);
  // o(rvrpTd);
  // o(rXSS);
  // o(rXDS);
  // o(rCSS);
  // o(rCDS);
  // gc;
}
