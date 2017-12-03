#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::highGainController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  (this->*mc_ptr)(config, info, model);

  thDes += dthRef*info.sim.dt;

  tau = kdHG*(dthRef - model.hoap2.all.dth) + kpHG*(thDes - model.hoap2.all.th);

  return tau;
}
