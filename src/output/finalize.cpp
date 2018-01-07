/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::finalize(Config &config)
{
  if(config.flag.debug) DEBUG;

  vector<double>().swap(data.t);

  vector<TreeModelList>().swap(data.tm);

  if(config.controller.name=="rlsDynamics")
    vector<RlsDynamicsList>().swap(data.dc);
}
