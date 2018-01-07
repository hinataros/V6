/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::index(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cop(config, info, model.hoap2);
  dcm(config, info, model.hoap2);
}
