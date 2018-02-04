/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decompose(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  Bc = bb_Rk*Bc_k;
  Bm = bb_Rk*Bm_k;

  // diff
  dBc = bb_dRk*Bc_k;
  dBm = bb_dRk*Bm_k;

  // ******************************
  cal_Pc = TB2k.transpose()*Bc;
  cal_Jc = Bc.transpose()*cal_J;

  cal_Pm = TB2k.transpose()*Bm;
  cal_Jm = Bm.transpose()*cal_J;

  // diff
  cal_dPc = dTB2k.transpose()*Bc + TB2k.transpose()*dBc;
  cal_dJc = Bc.transpose()*cal_dJ + dBc.transpose()*cal_J;

  cal_dPm = dTB2k.transpose()*Bm + TB2k.transpose()*dBm;
  cal_dJm = Bm.transpose()*cal_dJ + dBm.transpose()*cal_J;

  // ******************************
  cal_PcM = TC2k.transpose()*Bc;
  cal_PmM = TC2k.transpose()*Bm;

  // diff
  cal_dPcM = dTC2k.transpose()*Bc + TC2k.transpose()*dBc;
  cal_dPmM = dTC2k.transpose()*Bm + TC2k.transpose()*dBm;

  // ******************************
}
