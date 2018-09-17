/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rlsDynamics(const Config &config, Model &model, const double &t)
{
  if(debug) DEBUG;

  model.update(config.controller.dynamics);

  if(initialValueFlag)
    initialValue(config.dir.work, model);

  resize(model);
  index(model);

  if(configurationManager(config, model, t))
    reconfigure(model.hoap2.info);

  update(config.clock, model);

  trajectoryGenerator(model.hoap2.info.controlNodeNum, t);
  reference(model);

  controlMethod(config.controller.input, model.hoap2.info);

  outputConfig(config.controller.input, model.hoap2.info);

  return input;
}
