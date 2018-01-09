/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcm(Config &config, Info &info, TreeModel &hoap2)
{
  if(config.flag.debug) DEBUG;

  wX = sqrt(abs(hoap2.ag(2))/rC0(2));
  // wX = sqrt(abs(hoap2.ag(2))/hoap2.all.rC(2));

  rX = hoap2.all.rC + (hoap2.all.vC/wX);
}
