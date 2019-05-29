/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::vrpMomentum()
{
  if(debug) DEBUG;

  Vector3d rvrpRef = model->rX - fb.drXfb/model->wX;

  dpRef = model->M*model->wX*model->wX*(model->rC - rvrpRef);
}
