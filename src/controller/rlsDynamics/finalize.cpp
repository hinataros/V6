/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::finalize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  delete[] rkk;
}
