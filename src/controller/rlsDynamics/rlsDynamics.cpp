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

  if(t>=info.sim.twf+info.sim.tw0 && t<info.sim.tf){
    reset(config, info, t);
    reconfigure(config, info);
  }

  decompose(config, model);
  rename(config, info, model);

  reference(config, info, model, t);
  control(config, info, model);

  outputConfig(config, model);

  // smiyahra: 時間超えたらそれ用のyaml読みたい
  // if(t>info.sim.tf)
  //   tau *=0.;

  return input;
}
