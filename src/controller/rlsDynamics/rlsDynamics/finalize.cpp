/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::finalize()
{
  if(debug) DEBUG;

  delete[] info.constraint.c.controlNode;
  delete[] info.constraint.m.controlNode;

  delete[] yamlInfo.doc.sequenceKey;

  delete[] sequence;
  // delete[] rkk;

  des.finalize();
  controllerModel.finalize();
}
