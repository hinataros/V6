/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

void RLS::RlsDynamicsExtractor::resize()
{
  if(debug) DEBUG;

  footPrintList.clear();
  footPrintList.shrink_to_fit();

  controllers.controlMethod.clear();
  controllers.controlMethod.shrink_to_fit();
  controllers.desiredValueGenerator.clear();
  controllers.desiredValueGenerator.shrink_to_fit();
  controllers.feedbackController.clear();
  controllers.feedbackController.shrink_to_fit();
}
