/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::stateTriggerConfig(Config &config, Info &info, Model &model, double &t)
{
  return staticCheckContact(config, info, model, t);
  // return ankleStratagy(config, info, model, t);
  // return ankleHipStratagy(config, info, model, t);
}

bool RLS::RlsDynamics::sequenceTriggerConfig(Config &config, Info &info, double &t)
{
  int tint = round_cast(t, 3);
  int tfint = round_cast(info.sim.tf, 3);
  int tsumint = round_cast(info.sim.twf, 3) + round_cast(info.sim.tw0, 3);

  if(tint==tsumint&&tint<=tfint)
    return true;

  return false;
}
