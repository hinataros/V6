/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::crb()
{
  if(debug) DEBUG;

  tau = model->MthHat*ddthRef + model->cthHat - cal_JcHat.transpose()*cal_FcBarRef;
}
