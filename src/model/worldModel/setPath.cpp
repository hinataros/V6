/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "worldModel.hpp"

void RLS::WorldModel::setPath()
{
  if(debug) DEBUG;

  if(include.search=="relative")
    include.path = dir_share + "project/" + include.read;

  else if(include.search=="absolute")
    include.path = include.read;
}
