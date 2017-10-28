#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddthD(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  return -kthD*model.all.dth;
}
