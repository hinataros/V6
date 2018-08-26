/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rlsDynamics(Config &config, Model &model, double &t)
{
  if(debug) DEBUG;

  model.update(config.controller.dynamics);

  if(initialValueFlag)
    initialValue(model);

  resize(model);
  index(model);

  if(configurationManager(config, model, t))
    reconfigure(model.hoap2.info);

  update(model);

  trajectoryGenerator(t);
  reference(model);

  controlMethod(config.controller.input, model.hoap2.info);

  outputConfig(config.controller.input, model.hoap2.info);

  return input;
}
