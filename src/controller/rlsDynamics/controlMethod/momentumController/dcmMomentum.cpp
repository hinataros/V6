/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmMomentum(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  Vector3d rvrpRef = rX - drXRef/wX;

  dpRef = model.hoap2.all.m*wX*wX*(model.hoap2.all.rC - rvrpRef);
}
