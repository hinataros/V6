/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decomposeMix(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_PcM = TC2k.transpose()*Bc;
  cal_PmM = TC2k.transpose()*Bm;

  // diff
  cal_dPcM = dTC2k.transpose()*Bc + TC2k.transpose()*dBc;
  cal_dPmM = dTC2k.transpose()*Bm + TC2k.transpose()*dBm;
}
