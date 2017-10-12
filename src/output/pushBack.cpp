#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::pushBack(Config &config, double &t)
{
  if(config.flag.debug) DEBUG;

  data.t.push_back(t);

  data.tm.push_back(tm_temp);

  if(config.controller.name=="rlsVelocity")
    data.vc.push_back(vc_temp);
  if(config.controller.name=="rlsAcceleration")
    data.ac.push_back(ac_temp);
  if(config.controller.name=="rlsDynamics")
    data.dc.push_back(dc_temp);
}
