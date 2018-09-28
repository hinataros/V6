/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::controlMethod(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  if(this->info.input=="velocity"||this->info.input=="acceleration")
    input = (this->*motionController_ptr)(info);

  else if(this->info.input=="torque")
    input = (this->*inverseDynamicsController_ptr)(info);

  else
    input = VectorXd::Zero(info.dof.joint);
}
