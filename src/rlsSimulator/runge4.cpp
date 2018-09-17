/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::runge4(const Config &config, Model &model, RlsDynamics &rlsDynamics, Output &output)
{
  if(debug) DEBUG;

  // phase 1
  linkEqs(config, model, rlsDynamics, output);
  diffEqs(config, model, 0);
  integrator(model, 0, config.clock.dt/2);

  // phase 2
  t += config.clock.dt/2;
  linkEqs(config, model, rlsDynamics);
  diffEqs(config, model, 1);
  integrator(model, 1, config.clock.dt/2);

  // phase 3
  linkEqs(config, model, rlsDynamics);
  diffEqs(config, model, 2);
  integrator(model, 2, config.clock.dt);

  // phase 4
  t += config.clock.dt/2;
  linkEqs(config, model, rlsDynamics);
  diffEqs(config, model, 3);

  // update phase
  update(config.clock);
}
