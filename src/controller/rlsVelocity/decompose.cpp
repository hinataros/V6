#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::decompose(Config &config)
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
}
