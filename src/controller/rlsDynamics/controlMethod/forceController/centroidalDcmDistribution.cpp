/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDcmDistribution(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // o(cal_dLCRef + cal_GC);

  // Vector6d bm_wFR = Vector6d::Zero();
  // bm_wFR <<
  //   9.,9.,9.,9.,9.,9.;

  // Vector6d bm_wFL = Vector6d::Zero();
  // bm_wFL <<
  //   1.,1.,1.,1.,1.,1.;

  // MatrixXd W = MatrixXd::Zero(12,12);
  // W.block(0,0,6,6) = bm_wFR.asDiagonal();
  // W.block(6,6,6,6) = bm_wFL.asDiagonal();

  // o(W);

  // // VectorXd temp = bm_wFR + bm_wFL;
  // // MatrixXd tempM = temp.asDiagonal();
  // // MatrixXd tempMinv = tempM.inverse();
  // // VectorXd tempwtil = tempMinv.diagonal();

  // Vector6d bm_wTilde = (((bm_wFR + bm_wFL).asDiagonal()).inverse()).diagonal();

  // MatrixXd TW = MatrixXd::Zero(12,6);
  // TW.block(0,0,6,6) = (bm_wFL.asDiagonal()*bm_wTilde).asDiagonal();
  // TW.block(6,0,6,6) = (bm_wFR.asDiagonal()*bm_wTilde).asDiagonal();
  // o(TW);

  // cal_FcBarRef = pInv(cal_PcM, W)*(cal_dLCRef + cal_GC);
  // o(pInv(cal_PcM, W));
  // o(cal_FcBarRef);

  // Vector6d cal_FF = cal_FcBarRef.head(6) + cal_FcBarRef.tail(6);
  // o(cal_FF);

  // o(TW*cal_FF);
  // o(TW*cal_FF - cal_FcBarRef);

  // gc;

  // DCM-GI **************************************************************
  // cal_FcBarRef = pInv(cal_Pc, weight(config, info, model, 2, rX))*(cal_dLBRef + cal_GB);

  // // local CoP feedback
  // // **************************************************************
  // Vector2d nLtRef = 0.*cal_Ep.segment(6,6).segment(3,2);
  // Vector6d cal_FLRef = (Vector6d()<<Vector3d::Zero(), nLtRef, 0.).finished();

  // Vector2d nRtRef = -bb_Spx*Kpp*(F2rp(cal_F.segment(6,6)) - F2rp(cal_F.head(6)));
  // Vector6d cal_FRRef = (Vector6d()<<Vector3d::Zero(), nRtRef, 0.).finished();

  // VectorXd cal_FaBar = N(cal_PcM)*pInv(N(cal_PcM).block(0,0,6,12))*cal_FRRef;
  // cal_FcBarRef = pInv(cal_PcM, Wvrp)*(cal_dLCRef + cal_GC) + cal_FaBar;
  // // **************************************************************

  // VectorXd cal_FaBar = N(cal_PcM)*pInv(N(cal_PcM).block(6,0,6,12))*cal_FLRef;

  // MatrixXd WC = weight(info, rC);
  MatrixXd WX = weight(info, rX);
  MatrixXd Wvrp = weight(info, rX - drXDes/wX);

  MatrixXd Wvrpc = Bc.transpose()*Wvrp*Bc;

  cal_FcBarRef = pInv(cal_PcM, Wvrpc)*(cal_dLCRef + cal_GC);

  // // **************************************************************
  // cal_FcBarRef = pInv(cal_PcM, Wvrpc)*(cal_GC);
  // cal_FcBarRef.segment(6,6) += pInv(cal_PcM.block(0,6,6,6))*cal_dLCRef;
  // // **************************************************************

  // o(weight(config, info, model, 2, rX - drXDes/wX)(0,0));
  // o(weight(config, info, model, 2, rX - drXDes/wX)(6,6));

  // double wFRz = weight(config, info, model, 2, rX - drXDes/wX)(0,0);
  // double wFLz = weight(config, info, model, 2, rX - drXDes/wX)(6,6);

  // Vector6d bm_wFR = Vector6d::Zero();
  // bm_wFR <<
  //   wFRz,wFRz,wFRz,wFRz,wFRz,wFRz;

  // o(bm_wFR);
  // Vector6d bm_wFL = Vector6d::Zero();
  // bm_wFL <<
  //   wFLz,wFLz,wFLz,wFLz,wFLz,wFLz;

  // o(bm_wFL);

  // double wzTilde = 1/(wFRz + wFLz);

  // Vector6d bm_wTilde = Vector6d::Zero();
  // bm_wTilde <<
  //   wzTilde,wzTilde,wzTilde,wzTilde,wzTilde,wzTilde;

  // o(bm_wTilde);

  // MatrixXd WX = MatrixXd::Zero(12,6);
  // WX.block(0,0,6,6) = (bm_wFL.asDiagonal()*bm_wTilde).asDiagonal();
  // WX.block(6,0,6,6) = (bm_wFR.asDiagonal()*bm_wTilde).asDiagonal();
  // o(WX);

  // Vector6d temp = cal_FcBarRef.head(6) + cal_FcBarRef.tail(6);
  // o(temp);

  // o(WX*temp - cal_FcBarRef);
  // gc;
  // DCM-GI **************************************************************
}
