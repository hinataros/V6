#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decompose(Config &config)
{
  if(config.flag.debug) DEBUG;

  Bc = bb_Rk*Bc_k;
  Bm = bb_Rk*Bm_k;

  cal_Pc = TB2k.transpose()*Bc;
  cal_Jc = Bc.transpose()*cal_J;

  cal_Pm = TB2k.transpose()*Bm;
  cal_Jm = Bm.transpose()*cal_J;

  cal_PcM = TC2k.transpose()*Bc;
  cal_JcM = cal_Jc - cal_Pc.block(0,0,3,c).transpose()*BJC;

  // diff
  dBc = bb_dRk*Bc_k;
  dBm = bb_dRk*Bm_k;

  cal_dPc = dTB2k.transpose()*Bc + TB2k.transpose()*dBc;
  cal_dJc = Bc.transpose()*cal_dJ + dBc.transpose()*cal_J;

  cal_dPm = dTB2k.transpose()*Bm + TB2k.transpose()*dBm;
  cal_dJm = Bm.transpose()*cal_dJ + dBm.transpose()*cal_J;
}
