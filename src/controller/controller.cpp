#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"

VectorXd RLS::Controller::controller(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.name=="rlsDynamics")
    u = RlsDynamics::rlsDynamics(config, info, model, t);

  else
    cout << "no controller..." << endl;

  return u;
}
