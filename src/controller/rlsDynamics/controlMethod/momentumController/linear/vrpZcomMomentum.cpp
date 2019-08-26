/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::vrpZcomMomentum()
{
  if(debug) DEBUG;

  Vector3d rvrpRef = model->rX - fb.drXfb/model->wX;

  Vector3d vrpTemp = model->M*model->wX*model->wX*(model->rC - rvrpRef);
  Vector3d comTemp = model->M*fb.dvCfb;

  dpRef <<
    vrpTemp(0),
    vrpTemp(1),
    comTemp(2);
}
