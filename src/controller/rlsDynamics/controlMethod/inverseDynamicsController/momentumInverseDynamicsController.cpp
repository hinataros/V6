/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::momentumInverseDynamicsController()
{
  if(debug) DEBUG;

  // motion control
  (this->*motionController_ptr)();

  // momentum control
  (this->*momentumController_ptr)();

  // force control
  (this->*forceController_ptr)();

  // torque control
  (this->*torqueController_ptr)();

  return tau;
}
