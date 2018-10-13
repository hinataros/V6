/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::initializeInfo()
{
  if(debug) DEBUG;

  info.treeModelNum = 0;
  info.rigidBodyModelNum = 0;
}
