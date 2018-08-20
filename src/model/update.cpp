/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::update(const bool dynamics_flag)
{
  if(debug) DEBUG;

  hoap2.update(dynamics_flag);
  // object.update(config, info);
}
