/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decomposeBase(const Model &model)
{
  if(debug) DEBUG;

  cal_Pc = model.hoap2.all.TB2k.transpose()*Bc;
  cal_Jc = Bc.transpose()*model.hoap2.all.J;

  cal_Pm = model.hoap2.all.TB2k.transpose()*Bm;
  cal_Jm = Bm.transpose()*model.hoap2.all.J;

  // diff
  cal_dPc = model.hoap2.all.dTB2k.transpose()*Bc + model.hoap2.all.TB2k.transpose()*dBc;
  cal_dJc = Bc.transpose()*model.hoap2.all.dJ + dBc.transpose()*model.hoap2.all.J;

  cal_dPm = model.hoap2.all.dTB2k.transpose()*Bm + model.hoap2.all.TB2k.transpose()*dBm;
  cal_dJm = Bm.transpose()*model.hoap2.all.dJ + dBm.transpose()*model.hoap2.all.J;
}
