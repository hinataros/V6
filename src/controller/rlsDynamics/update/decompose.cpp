/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decompose()
{
  if(debug) DEBUG;

  Bc = model->bb_Rk*Bc_k;
  Bm = model->bb_Rk*Bm_k;

  // diff
  dBc = model->bb_dRk*Bc_k;
  dBm = model->bb_dRk*Bm_k;

  cal_Pc = model->bb_TB2k.transpose()*Bc;
  cal_Jc = Bc.transpose()*model->cal_J;

  cal_Pm = model->bb_TB2k.transpose()*Bm;
  cal_Jm = Bm.transpose()*model->cal_J;

  // diff
  cal_dPc = model->bb_dTB2k.transpose()*Bc + model->bb_TB2k.transpose()*dBc;
  cal_dJc = Bc.transpose()*model->cal_dJ + dBc.transpose()*model->cal_J;

  cal_dPm = model->bb_dTB2k.transpose()*Bm + model->bb_TB2k.transpose()*dBm;
  cal_dJm = Bm.transpose()*model->cal_dJ + dBm.transpose()*model->cal_J;

  cal_PcM = model->bb_TC2k.transpose()*Bc;
  cal_PmM = model->bb_TC2k.transpose()*Bm;

  // diff
  cal_dPcM = model->bb_dTC2k.transpose()*Bc + model->bb_TC2k.transpose()*dBc;
  cal_dPmM = model->bb_dTC2k.transpose()*Bm + model->bb_TC2k.transpose()*dBm;
}
