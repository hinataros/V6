/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::finalize()
{
  if(debug) DEBUG;

  vector<double>().swap(data.time);

  for(int i=0; i<info->treeModelNum; i++)
    vector<TreeModelList>().swap(data.treeModel[i].vec);

  for(int i=0; i<controllerNum; i++)
    vector<RlsDynamicsList>().swap(data.rlsDynamics[i].vec);

  vector<ExtList>().swap(data.ext);

  delete[] treeModelList_temp;
  delete[] rlsDynamicsList_temp;

  delete[] data.treeModel;
  delete[] data.rlsDynamics;
}
