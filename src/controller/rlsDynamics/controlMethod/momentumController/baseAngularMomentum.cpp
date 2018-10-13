/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseAngularMomentum()
{
  if(debug) DEBUG;

  dlBRef =
    -model->M*cross(model->rB2C).transpose()*fb.dvCfb + model->IC*fb.dwBfb
    -model->M*cross(model->drB2C).transpose()*model->wB + model->dIC*model->wB;
}
