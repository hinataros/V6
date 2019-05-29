/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalAngularMomentumDamping()
{
  if(debug) DEBUG;

  dlCRef = model->IC * fb.dwBfb + model->dIC * model->wB - KDlC * model->HC * model->dth;
}
