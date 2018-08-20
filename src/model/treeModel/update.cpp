/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::update(const bool dynamics_flag)
{
  if(debug) DEBUG;

  position();
  velocity();

  if(dynamics_flag){
    identityVectorMethod();
    analyticalDynamics();
  }

  // outputConfig(config, info);
}
