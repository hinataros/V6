/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputConfig(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  if(this->info.input=="velocity")
    velocityOutputConfig(info);

  else if(this->info.input=="acceleration")
    accelerationOutputConfig(info);

  else if(this->info.input=="torque")
    torqueOutputConfig(info);
}
