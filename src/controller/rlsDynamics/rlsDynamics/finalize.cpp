/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

void RLS::RlsDynamics::finalize()
{
  if(debug) DEBUG;

  ext->finalize(this);
  delete ext;

  delete[] yamlInfo.doc.sequenceKey;

  delete[] sequence;
  // delete[] rkk;

  des.finalize();
  constraintModel.finalize();
  controllerModel.finalize();
}
