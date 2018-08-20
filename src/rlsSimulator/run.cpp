/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::run(Config &config, Model &model, RlsDynamics &rlsDynamics, Output &output)
{
  if(debug) DEBUG;

  initialParameter(config.clock, model.hoap2);

  for(int i=0; i<config.clock.n; i++){
    cout << "\r" << t << " / " << config.clock.tf;
    t = config.clock.t0 + i*config.clock.dt;

    runge4(config, model, rlsDynamics, output);

  } cout << endl;

  // linkEqs(config, info, model, controller, output);

  // output.output(config, info);

  // finalize(config, info, model, controller, output);
}
