/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcm2com(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  dvCRef = wX*(drXRef - model.hoap2.all.vC);
}
