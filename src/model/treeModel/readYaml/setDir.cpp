/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::setDir(string dir_share)
{
  if(debug) DEBUG;

  info.path.body = dir_share + "model/" + info.name.body + ".body";
  info.path.cnoid = dir_share + "project/" + info.name.cnoid + ".cnoid";
}
