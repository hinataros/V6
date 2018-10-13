/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::setModelInfo(Info &info)
{
  if(debug) DEBUG;

  this->info.all = info;

  this->info.controlModelID = info.modelID[config.controlModel];
  this->info.model = info.treeModel[this->info.controlModelID];
}
