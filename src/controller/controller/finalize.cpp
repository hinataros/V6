/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"

void RLS::Controller::finalize()
{
  if(debug) DEBUG;

  delete[] rlsDynamics;
}
