/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"

void RLS::Controller::finalize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.name=="rlsDynamics")
    RlsDynamics::finalize(config, info);

  else
    cout << "no controller..." << endl;
}
