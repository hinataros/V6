/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mixedmixedOpt()
{
  if(debug) DEBUG;

  MatrixXd MthHatBar = MatrixXd::Zero(info.model.dof.joint, info.model.dof.all);
  MthHatBar <<
    model->HMth.transpose(), model->MthC;

  tau = MthHatBar*ddqMoptRef + model->cthC + model->gth - cal_Jc.transpose()*cal_FcBarRef;

  // MatrixXd A = MatrixXd::Zero(info.model.dof.joint, 3+info.model.dof.joint);
  // A <<
  //   model->HC.transpose(), model->MthC;

  // tau = A*ddqwoptRef + model->cthC + model->gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = HMth.transpose()*cal_dVMRef + MthC*ddthRef + model->cthC + model->gth - cal_Jc.transpose()*cal_FcBarRef;
}
