/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::staticControl()
{
  if(debug) DEBUG;

  tau = model->gth - constraintModel.cal_Jc.transpose()*cal_FcBarRef;

  // tau = Nast(cal_Jc, model->Mth)*Mth*ddthD(config, model) + model->gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = Nast(cal_JcM, model->Mth)*MthC*ddthD(info) + model->gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = MthC*ddthD() + model->gth - cal_Jc.transpose()*cal_FcBarRef;
}
