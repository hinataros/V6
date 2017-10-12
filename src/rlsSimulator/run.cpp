#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::run(Config &config, Info &info, Model &model, Controller &controller, Output &output)
{
  if(config.flag.debug) DEBUG;

  initialParameter(config, info, model);

  for(int i=0; i<info.sim.n; i++){
    cout << "\r" << t << " / " << info.sim.tf;
    t = info.sim.t0 + i*info.sim.dt;

    runge4(config, info, model, controller, output);

  } cout << endl;

  linkEqs(config, info, model, controller, output);

  output.output(config, info);

  finalize(config, info, model, output);
}
