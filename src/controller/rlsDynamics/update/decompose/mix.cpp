/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decomposeMix(Model &model)
{
  if(debug) DEBUG;

  cal_PcM = model.hoap2.all.TC2k.transpose()*Bc;
  cal_PmM = model.hoap2.all.TC2k.transpose()*Bm;

  // diff
  cal_dPcM = model.hoap2.all.dTC2k.transpose()*Bc + model.hoap2.all.TC2k.transpose()*dBc;
  cal_dPmM = model.hoap2.all.dTC2k.transpose()*Bm + model.hoap2.all.TC2k.transpose()*dBm;
}
