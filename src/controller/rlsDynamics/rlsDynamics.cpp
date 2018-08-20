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

  // if(configurationManager(config, info, model, t))
  //   reconfigure(config, info);

  // update(config, info, model);

  // reference(config, info, model, t);
  // controlMethod(config, info, model);

  // outputConfig(config, info, model);

  // return input;
  return VectorXd(model.hoap2.info.dof.all);
}
