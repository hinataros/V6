/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decompose(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  basis(config, model);

  decomposeBase(config, model);
  decomposeMix(config, model);
}
