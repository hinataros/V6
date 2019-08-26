/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::vrpMomentumwXt()
{
  if(debug) DEBUG;

  double wXtv = model->wXt - (model->dwXt/model->wXt);
  double wXtvMom = (model->wXt*model->wXt) / ((model->wXt*model->wXt)-model->dwXt);

  Vector3d rvrpRef = model->rXt - fb.drXtfb/wXtv;

  dpRef = model->M* wXtvMom *(model->rC - rvrpRef);
}
