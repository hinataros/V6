/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::setModelParameterInclude(const string &dir_share)
{
  if(debug) DEBUG;

  if(include_mp.search=="relative")
    include_mp.path = dir_share + "model/" + include_mp.read;
  else if(include_mp.search=="absolute")
    include_mp.path = include_mp.read;
}

void RLS::TreeModel::setInitialConfigurationInclude(const string &dir_share)
{
  if(debug) DEBUG;

  if(include_ic.search=="relative")
    include_ic.path = dir_share + "project/" + include_ic.read;
  else if(include_ic.search=="absolute")
    include_ic.path = include_ic.read;
}
