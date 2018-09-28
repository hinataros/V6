/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::finalize()
{
  if(debug) DEBUG;

  delete[] rkk;

  delete[] desiredControlNodeAccelerationGeneratorNum;
  delete[] desiredControlNodeAccelerationGeneratorName;
  delete[] desiredControlNodeWrenchGeneratorNum;
  delete[] desiredControlNodeWrenchGeneratorName;
  delete[] map_desiredControlNodeAccelerationGenerator;
  delete[] map_desiredControlNodeWrenchGenerator;
  free(desiredControlNodeAccelerationGenerator_ptr);
  free(desiredControlNodeWrenchGenerator_ptr);
}
