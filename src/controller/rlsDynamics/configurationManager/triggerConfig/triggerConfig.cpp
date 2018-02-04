/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::stateTriggerConfig(Config &config, Info &info, Model &model, double &t)
{
  return checkContact(config, info, model, t);
  // return ankleStratagy(config, info, model, t);
  // return ankleHipStratagy(config, info, model, t);
}

bool RLS::RlsDynamics::sequenceTriggerConfig(Config &config, Info &info, double &t)
{
  if(t>=info.sim.twf+info.sim.tw0 && t<info.sim.tf)
    return true;
}
