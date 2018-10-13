/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::update()
{
  if(debug) DEBUG;

  for(int i=0; i<info.treeModelNum; i++)
    treeModel[i].update();
  for(int i=0; i<info.rigidBodyModelNum; i++)
    rigidBodyModel[i].update();
}
