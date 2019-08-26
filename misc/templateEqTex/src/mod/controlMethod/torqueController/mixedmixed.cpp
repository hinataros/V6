/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mixedmixed()
{
  if(debug) DEBUG;

  MatrixXd MthHatBar = MatrixXd::Zero(info.model.dof.joint, info.model.dof.all);
  MthHatBar <<
    model->HMth.transpose(), model->MthC;

  tau = MthHatBar*ddqMRef + model->cthC + model->gth - constraintModel.cal_Jc.transpose()*cal_FcBarRef;
}
