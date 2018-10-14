/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

void RLS::Ext::defaultController(RlsDynamics *io)
{
  if(debug) DEBUG;

}

VectorXd RLS::Ext::defaultJointController(RlsDynamics *io)
{
  if(debug) DEBUG;

  return VectorXd::Zero(io->info.model.dof.joint);
}

VectorXd RLS::Ext::defaultConfigurationController(RlsDynamics *io)
{
  if(debug) DEBUG;

  return VectorXd::Zero(io->info.model.dof.all);
}
