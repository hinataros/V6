/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddqthD(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  VectorXd ddthD = -KDth*model.hoap2.all.dth;

  return (VectorXd(info.dof.all)<<Vector6d::Zero(), ddthD).finished();
}
