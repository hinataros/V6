/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddqthinit(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  VectorXd ddthinit = -KDth*model.hoap2.all.dth + Kthinit*(th0 - model.hoap2.all.th);

  return (VectorXd(info.dof.all)<<Vector6d::Zero(), ddthinit).finished();
}
