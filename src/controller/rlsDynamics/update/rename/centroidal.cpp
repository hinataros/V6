/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameCentroidal(TreeModel &model)
{
  if(debug) DEBUG;

  // ******************************
  // inertia
  if(MB.determinant())
    MthHat = Mth - HBth.transpose()*MB.inverse()*HBth;

  // nonlinear
  if(MB.determinant())
    cthHat = cth - HBth.transpose()*MB.inverse()*cal_CB;
  // ******************************

  // centroidal
  // ******************************
  Pcf = cal_Pc.block(0,0,3,model.info.contact.c.all);
  Pmf = cal_Pm.block(0,0,3,model.info.contact.m.all);
  PcMm = cal_PcM.block(3,0,3,model.info.contact.c.all);
  cal_JcM = cal_Jc - Pcf.transpose()*model.all.JB2C;
  cal_JmM = cal_Jm - Pmf.transpose()*model.all.JB2C;

  // diff
  dPcf = cal_dPc.block(0,0,3,model.info.contact.c.all);
  dPmf = cal_dPm.block(0,0,3,model.info.contact.m.all);
  dPcMm = cal_dPc.block(3,0,3,model.info.contact.c.all);
  // dPcf = 0と仮定
  cal_dJcM = cal_dJc - Pcf.transpose()*model.all.dJB2C;
  cal_dJmM = cal_dJm - Pmf.transpose()*model.all.dJB2C;

  // ******************************
  if(IC.determinant())
    Jth <<
      model.all.JB2C,
      IC.inverse()*HC;

  cal_JcHat = cal_Jc - cal_PcM.transpose()*Jth;
  cal_JmHat = cal_Jm - cal_PmM.transpose()*Jth;

  // diff
  if(IC.determinant())
    dJth <<
      model.all.dJB2C,
      IC.inverse()*(dHC - dIC*(IC.inverse()*HC));

  cal_dJcHat = cal_dJc - cal_dPcM.transpose()*Jth - cal_PcM.transpose()*dJth;
  cal_dJmHat = cal_dJm - cal_dPmM.transpose()*Jth - cal_PmM.transpose()*dJth;
}
