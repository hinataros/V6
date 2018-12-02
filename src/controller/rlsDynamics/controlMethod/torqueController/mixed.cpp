/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mixed()
{
  if(debug) DEBUG;

  MatrixXd MthHatBar = MatrixXd::Zero(info.model.dof.joint, info.model.dof.all);
  MthHatBar <<
    model->HMth.transpose(), model->MthC;

  tau = MthHatBar*ddqMRef + model->cthC - constraintModel.cal_JcM.transpose()*cal_FcBarRef;
}
