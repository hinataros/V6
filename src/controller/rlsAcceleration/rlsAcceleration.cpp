#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsAcceleration.hpp"

VectorXd RLS::RlsAcceleration::rlsAcceleration(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  model.update(config, info);

  if(t==0.)
    initialValue(config, info, model);

  rename(config, info, model);
  resize(config, info, model);

  if(t>=info.sim.twf+info.sim.tw0 && t<info.sim.tf){
    reset(config, info, t);
    reconfigure(config, info);
  }

  decompose(config);

  baseReference(config, info, model, t);
  endEffectorReference(config, info, model, t);

  accelerationController(config, model);

  outputConfig(config);

  return ddqRef;
}
