/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::controlMethod()
{
  if(debug) DEBUG;

  if(config.input=="velocity"||config.input=="acceleration")
    input = (this->*motionController_ptr)();

  else if(config.input=="torque")
    input = (this->*inverseDynamicsController_ptr)();

  else
    input = VectorXd::Zero(info.model.dof.joint);

  (this->*externalWrenchController_ptr)();
}
