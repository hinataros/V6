/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeControllerDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.name=="rlsDynamics")
    makeRlsDynamicsDat(config, info);
}
