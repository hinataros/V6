#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::deleteModel(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<info.value.node; i++)
    delete[] limb[i].node;

  delete[] limb;
}
