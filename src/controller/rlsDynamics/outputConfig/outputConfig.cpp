/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputConfig(const string controlInput, const TreeModel::Info &info)
{
  if(debug) DEBUG;

  if(controlInput=="velocity")
    velocityOutputConfig(info);

  else if(controlInput=="acceleration")
    accelerationOutputConfig(info);

  else if(controlInput=="torque")
    torqueOutputConfig(info);
}
