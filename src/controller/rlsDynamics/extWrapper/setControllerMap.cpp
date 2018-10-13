/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::ExtWrapper::setControllerMap(RlsDynamics *rlsDynamics)
{
  if(debug) DEBUG;

  o("wrapper");
#ifdef EXT
  ext.setControllerMap(rlsDynamics);
#endif
}

