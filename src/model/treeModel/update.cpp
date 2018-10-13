/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::update()
{
  if(debug) DEBUG;

  position();
  velocity();

  if(dynamics_flag){
    identityVectorMethod();
    analyticalDynamics();
  }

  outputConfig();
}
