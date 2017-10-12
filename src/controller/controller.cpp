#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"

VectorXd RLS::Controller::controller(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.name=="rlsVelocity")
    u = RlsVelocity::rlsVelocity(config, info, model, t);
  else if(config.controller.name=="rlsAcceleration")
    u = RlsAcceleration::rlsAcceleration(config, info, model, t);

  else
    cout << "no controller..." << endl;

  return u;
}
