/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::setInitialBoundary()
{
  if(debug) DEBUG;

  rB0 = model->rB0;
  qB0 = Quaternion4d::R2q(model->RB0);

  for(int i=0; i<info->controlNodeNum; i++){
    r0[i] = model->r0[i];
    rfabs[i] = model->r0[i];

    q0[i] = Quaternion4d::R2q(model->R0[i]);
    qfabs[i] = Quaternion4d::R2q(model->R0[i]);
  }

  rC0 = model->rC0;
  rX0 = model->rX0;

  cal_Fext0 = model->cal_FB0;
}
