/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameCentroidal(const TreeModel &model)
{
  if(debug) DEBUG;

  // inertia
  if(MB.determinant())
    MthHat = Mth - HBth.transpose()*MB.inverse()*HBth;

  // nonlinear
  if(MB.determinant())
    cthHat = cth - HBth.transpose()*MB.inverse()*cal_CB;
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
