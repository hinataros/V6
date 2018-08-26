/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::rename(Model &model)
{
  if(debug) DEBUG;

  renameState(model.hoap2);
  renameBase(model.hoap2);
  renameMix(model.hoap2);
  renameCentroidal(model.hoap2);
  renameOthers(model);

  renameDebug(model);
}
