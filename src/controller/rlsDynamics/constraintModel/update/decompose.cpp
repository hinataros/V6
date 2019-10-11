/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::decompose()
{
  if(debug) DEBUG;

  Bc = model->bb_Rk*Bc_k;
  Bm = model->bb_Rk*Bm_k;

  // diff
  dBc = model->bb_dRk*Bc_k;
  dBm = model->bb_dRk*Bm_k;

  mbb_Cc = model->bb_TB2k.transpose()*Bc;
  cal_Jc = Bc.transpose()*model->cal_J;

  mbb_Cm = model->bb_TB2k.transpose()*Bm;
  cal_Jm = Bm.transpose()*model->cal_J;

  // diff
  mbb_dCc = model->bb_dTB2k.transpose()*Bc + model->bb_TB2k.transpose()*dBc;
  cal_dJc = Bc.transpose()*model->cal_dJ + dBc.transpose()*model->cal_J;

  mbb_dCm = model->bb_dTB2k.transpose()*Bm + model->bb_TB2k.transpose()*dBm;
  cal_dJm = Bm.transpose()*model->cal_dJ + dBm.transpose()*model->cal_J;

  mbb_CcM = model->bb_TC2k.transpose()*Bc;
  mbb_CmM = model->bb_TC2k.transpose()*Bm;

  // diff
  mbb_dCcM = model->bb_dTC2k.transpose()*Bc + model->bb_TC2k.transpose()*dBc;
  mbb_dCmM = model->bb_dTC2k.transpose()*Bm + model->bb_TC2k.transpose()*dBm;

  V_cwc = compute_CWC_span();
}
