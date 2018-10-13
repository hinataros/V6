/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseOpt()
{
  if(debug) DEBUG;

  MatrixXd MthBar = MatrixXd::Zero(info.model.dof.joint, info.model.dof.all);
  MthBar <<
    model->HBth.transpose(), model->Mth;

  tau = MthBar*ddqBoptRef + model->cth + model->gth - cal_Jc.transpose()*cal_FcBarRef;
}
