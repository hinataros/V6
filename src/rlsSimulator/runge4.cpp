/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::runge4(Model &model, Controller &controller, Output &output)
{
  if(debug) DEBUG;

  // phase 1
  linkEqs(model, controller, output);
  diffEqs(0, model);
  integrator(0, model.worldModel.dt/2, model);

  // phase 2
  t += model.worldModel.dt/2;
  linkEqs(model, controller);
  diffEqs(1, model);
  integrator(1, model.worldModel.dt/2, model);

  // phase 3
  linkEqs(model, controller);
  diffEqs(2, model);
  integrator(2, model.worldModel.dt, model);

  // phase 4
  t += model.worldModel.dt/2;
  linkEqs(model, controller);
  diffEqs(3, model);

  // update phase
  update(model.info, model.worldModel.dt);
}
