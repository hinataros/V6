/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::jointSpace(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  tau = Mth*ddthRef + cth + gth;
}
