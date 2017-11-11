#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::finalize(Config &config)
{
  if(config.flag.debug) DEBUG;

  vector<TreeModelList>().swap(data.tm);

  if(config.controller.name=="rlsDynamics"){
    if(config.solver.input=="velocity")
      vector<RlsVelocityList>().swap(data.vc);
    else if(config.solver.input=="acceleration")
      vector<RlsAccelerationList>().swap(data.ac);
    else if(config.solver.input=="torque")
      vector<RlsDynamicsList>().swap(data.dc);
  }
}
