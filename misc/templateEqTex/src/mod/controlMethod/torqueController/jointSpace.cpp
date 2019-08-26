/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::jointSpace()
{
  if(debug) DEBUG;

  tau = model->Mth*ddthRef + model->cth + model->gth;
}
