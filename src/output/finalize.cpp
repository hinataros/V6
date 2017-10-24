#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::finalize(Config &config)
{
  if (config.flag.debug) DEBUG;

  vector<TreeModelList>().swap(data.tm);

  if(config.controller.name=="rlsVelocity")
    vector<RlsVelocityList>().swap(data.vc);
  if(config.controller.name=="rlsAcceleration")
    vector<RlsAccelerationList>().swap(data.ac);
  if(config.controller.name=="rlsDynamics")
    vector<RlsDynamicsList>().swap(data.dc);
}
