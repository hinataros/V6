/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rlsDynamics(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  model.update(config, info);

  if(initialValueFlag)
    initialValue(config, info, model);

  resize(config, info, model);
  index(config, info, model);

  if(configurationManager(config, info, model, t))
    reconfigure(config, info);

  update(config, info, model);

  reference(config, info, model, t);
  controlMethod(config, info, model);

  outputConfig(config, info, model);

  return input;
}
