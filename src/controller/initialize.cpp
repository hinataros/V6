#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"

void RLS::Controller::initialize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.name=="rlsVelocity")
    RlsVelocity::initialize(config, info);
  else if(config.controller.name=="rlsAcceleration")
    RlsAcceleration::initialize(config, info);

  else
    cout << "no controller..." << endl;
}
