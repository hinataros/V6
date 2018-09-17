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

  delete[] controlNodeTrajectoryNum;
  delete[] controlNodeTrajectoryName;
  delete[] map_controlNodeTrajectory;
  free(controlNodeTrajectory_ptr);
}
