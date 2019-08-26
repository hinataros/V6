/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerModel.hpp"

void RLS::ControllerModel::finalize()
{
  if(debug) DEBUG;

  for(int i=0; i<info->treeModelNum; i++)
    treeModel[i].finalize();

  delete[] treeModel;
}
