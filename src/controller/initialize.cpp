/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"

void RLS::Controller::initialize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.name=="rlsDynamics")
    RlsDynamics::initialize(config, info);

  else
    cout << "no controller..." << endl;
}
