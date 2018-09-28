/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::update()
{
  if(debug) DEBUG;

  position();
  velocity();

  if(info.dynamics_flag){
    identityVectorMethod();
    analyticalDynamics();
  }

  outputConfig();
}
