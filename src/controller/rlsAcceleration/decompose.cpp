#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsAcceleration.hpp"

void RLS::RlsAcceleration::decompose(Config &config)
{
  if(config.flag.debug) DEBUG;

  Bc = bb_Rk*Bc_k;
  Bm = bb_Rk*Bm_k;

  cal_Pc.transpose() = Bc.transpose()*bb_Tk2B;
  cal_Jc = Bc.transpose()*cal_J;

  cal_Pm.transpose() = Bm.transpose()*bb_Tk2B;
  cal_Jm = Bm.transpose()*cal_J;

  // diff
  dBc = bb_dRk*Bc_k;
  dBm = bb_dRk*Bm_k;

  cal_dPc.transpose() = Bc.transpose()*bb_dTk2B + dBc.transpose()*bb_Tk2B;
  cal_dJc = Bc.transpose()*cal_dJ + dBc.transpose()*cal_J;

  cal_dPm.transpose() = Bm.transpose()*bb_dTk2B + dBm.transpose()*bb_Tk2B;
  cal_dJm = Bm.transpose()*cal_dJ + dBm.transpose()*cal_J;
}
