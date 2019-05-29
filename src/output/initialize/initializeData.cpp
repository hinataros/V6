/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::initializeData()
{
  if(debug) DEBUG;

  data.treeModel = new TreeModelData[info->treeModelNum];
  data.rlsDynamics = new RlsDynamicsData[controllerNum];

  treeModelList_temp = new TreeModelList[info->treeModelNum];
  rlsDynamicsList_temp = new RlsDynamicsList[controllerNum];

  footPrintList_op.clear();
  footPrintList_op.shrink_to_fit();
}
