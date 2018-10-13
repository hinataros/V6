/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::pushBack(const double &t)
{
  if(debug) DEBUG;

  data.time.push_back(t);

  for(int i=0; i<info->treeModelNum; i++)
    data.treeModel[i].vec.push_back(treeModelList_temp[i]);

  for(int i=0; i<controllerNum; i++)
    data.rlsDynamics[i].vec.push_back(rlsDynamicsList_temp[i]);
}
