/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rlsDynamics(const Config &config, Model &model, const double &t)
{
  if(debug) DEBUG;

  model.update();

  if(initialValueFlag)
    initialValue(model);

  resize(model);
  index(model);

  if(configurationManager(config, model, t))
    reconfigure(model.hoap2.info);

  update(config.clock, model);

  desiredValueGenerator(model.hoap2.info.controlNodeNum, t);
  feedbackController(model);

  controlMethod(model.hoap2.info);

  outputConfig(model.hoap2.info);

  return input;
}
