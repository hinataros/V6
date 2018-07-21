/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decomposeBase(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_Pc = TB2k.transpose()*Bc;
  cal_Jc = Bc.transpose()*cal_J;

  cal_Pm = TB2k.transpose()*Bm;
  cal_Jm = Bm.transpose()*cal_J;

  // diff
  cal_dPc = dTB2k.transpose()*Bc + TB2k.transpose()*dBc;
  cal_dJc = Bc.transpose()*cal_dJ + dBc.transpose()*cal_J;

  cal_dPm = dTB2k.transpose()*Bm + TB2k.transpose()*dBm;
  cal_dJm = Bm.transpose()*cal_dJ + dBm.transpose()*cal_J;
}
