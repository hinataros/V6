/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputConfig()
{
  if(debug) DEBUG;

  outputDesConfig();
  outputErrConfig();
  outputRefConfig();
  outputIndexConfig();
  // outputIndexPrintConfig();

  outputExtConfig();
}
