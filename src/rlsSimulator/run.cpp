/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::run(Model &model, Controller &controller, Output &output)
{
  if(debug) DEBUG;

  initialParameter(model);

  for(int i=0; i<model.worldModel.n; i++){
    cout << "\r" << t << " / " << model.worldModel.tf;
    t = model.worldModel.t0 + i*model.worldModel.dt;

    runge4(model, controller, output);

  } cout << endl;

  linkEqs(model, controller, output);

  output.output();
}
