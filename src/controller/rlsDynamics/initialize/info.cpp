/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeInfo(const string &path_work)
{
  if(debug) DEBUG;

  this->info.path_work = path_work;

  this->info.input = "no input";
  this->info.driven = "flow";
  this->info.trigger = "default";
}
