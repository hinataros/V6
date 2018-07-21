/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::update(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  transform(config, info, model);
  decompose(config, model);
  objective(config, info, model);
  rename(config, info, model);
}
