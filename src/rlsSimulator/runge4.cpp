#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::runge4(Config &config, Info &info, Model &model, Controller &controller, Output &output)
{
  if(config.flag.debug) DEBUG;

  // // phase 1
  linkEqs(config, info, model, controller, output);
  diffEqs(config, info, model, 0);
  integrator(config, model, 0, info.sim.dt/2);

  // phase 2
  t += info.sim.dt/2;
  linkEqs(config, info, model, controller);
  diffEqs(config, info, model, 1);
  integrator(config, model, 1, info.sim.dt/2);

  // phase 3
  linkEqs(config, info, model, controller);
  diffEqs(config, info, model, 2);
  integrator(config, model, 2, info.sim.dt);

  // phase 4
  t += info.sim.dt/2;
  linkEqs(config, info, model, controller);
  diffEqs(config, info, model, 3);

  // update phase
  update(config, info, model);
}
