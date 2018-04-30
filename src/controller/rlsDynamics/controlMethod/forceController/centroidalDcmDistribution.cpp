/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDcmDistribution(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

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

  // DCM-GI **************************************************************
  // cal_FcBarRef = pInv(cal_Pc, weight(config, info, model, 2, rX))*(cal_dLBRef + cal_GB);

  cal_FcBarRef = pInv(cal_PcM, weight(config, info, model, 2, rX))*(cal_dLCRef + cal_GC);

  // o(weight(config, info, model, 2, rX)(0,0));
  // o(weight(config, info, model, 2, rX)(6,6));

  // double wFRz = weight(config, info, model, 2, rX)(0,0);
  // double wFLz = weight(config, info, model, 2, rX)(6,6);

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
  // DCM-GI **************************************************************
}
