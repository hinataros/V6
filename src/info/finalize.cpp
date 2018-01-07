/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"

void RLS::Info::finalize(Config &config)
{
  if(config.flag.debug) DEBUG;

  delete[] limb;
}
