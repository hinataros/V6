/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputConfig(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  torqueOutputDesConfig(config, info, model);
  torqueOutputErrConfig(config, info, model);
  torqueOutputRefConfig(config, info, model);
  torqueOutputIndexConfig(config, info, model);
  torqueOutputIndexPrintConfig(config, info, model);
}
