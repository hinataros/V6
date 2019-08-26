/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::centroidal()
{
  if(debug) DEBUG;

  // inertia
  if(MB.determinant())
    MthHat = Mth - HBth.transpose()*MB.inverse()*HBth;

  // nonlinear
  if(MB.determinant())
    cthHat = cth - HBth.transpose()*MB.inverse()*cal_CB;

  if(IC.determinant())
    Jth <<
      model->all.JB2C,
      IC.inverse()*HC;

  // diff
  if(IC.determinant())
    dJth <<
      model->all.dJB2C,
      IC.inverse()*(dHC - dIC*(IC.inverse()*HC));
}
