/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::setInitialBoundary()
{
  if(debug) DEBUG;

  rC0 = model->rC0;

  rB0 = model->rB0;
  xiB0 = model->xiB0;

  rX0 = model->rX0;

  cal_X0 = model->cal_X0;

  cal_Fext0 = model->cal_FB0;

  for(int i=0; i<yamlInfo->sequenceNum; i++)
    sequence[i].cal_Xfabs = cal_X0;
}
