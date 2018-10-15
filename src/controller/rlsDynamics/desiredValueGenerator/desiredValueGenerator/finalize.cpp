/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::finalize()
{
  if(debug) DEBUG;

  delete[] sequence;

  delete[] desiredControlNodeMotionGeneratorNum;
  delete[] desiredControlNodeMotionGeneratorName;
  delete[] desiredControlNodeForceGeneratorNum;
  delete[] desiredControlNodeForceGeneratorName;
  delete[] desiredControlNodeMotionGenerator_map;
  delete[] desiredControlNodeForceGenerator_map;
  free(desiredControlNodeMotionGenerator_ptr);
  free(desiredControlNodeForceGenerator_ptr);
}
