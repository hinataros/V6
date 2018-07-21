/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::rename(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  renameBase(config, info, model);
  renameMix(config, info, model);
  renameCentroidal(config, info, model);
  renameOthers(config, info, model);

  renameDebug(config, info, model);
}
