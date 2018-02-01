/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::zeroMotion(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  return VectorXd::Zero(info.dof.all);
}
