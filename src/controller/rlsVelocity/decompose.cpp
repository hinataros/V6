#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::decompose(Config &config)
{
  if(config.flag.debug) DEBUG;

  Bc = bb_Rk*Bc_k;
  Bm = bb_Rk*Bm_k;

  cal_Pc.transpose() = Bc.transpose()*bb_Tk2B;
  cal_Jc = Bc.transpose()*cal_J;

  cal_Pm.transpose() = Bm.transpose()*bb_Tk2B;
  cal_Jm = Bm.transpose()*cal_J;
}
