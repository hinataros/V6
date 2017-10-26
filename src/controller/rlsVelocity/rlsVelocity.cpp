#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

VectorXd RLS::RlsVelocity::rlsVelocity(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  model.update(config, info);

  if(t==0.)
    initialValue(config, info, model);

  resize(config, info, model);

  if(t>=info.sim.twf+info.sim.tw0 && t<info.sim.tf){
    reset(config, info, t);

    reconfigure(config, info);
  }

  rename(config, info, model);
  decompose(config);

  reference(config, info, model, t);
  velocityController(config);

  outputConfig(config);

  return dqRef;
}
