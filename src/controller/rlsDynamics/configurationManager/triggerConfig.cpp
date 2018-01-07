/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::stateTriggerConfig(Config &config, Info &info, Model &model, double &t)
{
  // default and initial state
  if(cal_FextRef.norm()==0.)
    return 0;

  if(cal_FextRef.norm()!=0.)
    return 1;

  return -1;
}

bool RLS::RlsDynamics::sequenceTriggerConfig(Config &config, Info &info, double &t)
{
  if(t>=info.sim.twf+info.sim.tw0 && t<info.sim.tf)
    return true;
}
