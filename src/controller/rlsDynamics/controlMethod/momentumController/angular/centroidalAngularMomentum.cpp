/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalAngularMomentum()
{
  if(debug) DEBUG;

  dlCRef = model->IC*fb.dwBfb + model->IC*model->wB;
}
