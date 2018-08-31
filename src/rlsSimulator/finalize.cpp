/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::finalize(Model &model, RlsDynamics &rlsDynamics, Output &output)
{
  if(debug) DEBUG;

  rlsDynamics.finalize();
  output.finalize();
  model.deleteModel();
}
