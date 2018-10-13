/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::setID()
{
  if(debug) DEBUG;

  for(int i=0; i<info.treeModelNum; i++)
    info.modelID[info.treeModel[i].name] = i;
  for(int i=0; i<info.rigidBodyModelNum; i++)
    info.modelID[info.rigidBodyModel[i].name] = i;
}
