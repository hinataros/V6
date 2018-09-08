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

  delete[] endEffectorTrajectoryNum;
  delete[] endEffectorTrajectoryName;
  delete[] map_endEffectorTrajectory;
  free(endEffectorTrajectory_ptr);
}
