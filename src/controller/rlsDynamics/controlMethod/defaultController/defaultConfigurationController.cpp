/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::defaultConfigurationController()
{
  if(debug) DEBUG;

  return VectorXd::Zero(info.model.dof.all);
}