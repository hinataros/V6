/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::fullDynamicsController()
{
  if(debug) DEBUG;

  // momentum control
  (this->*momentumController_ptr)();

  // motion control
  (this->*motionController_ptr)();

  // force control
  (this->*forceController_ptr)();

  // torque control
  (this->*torqueController_ptr)();

  return tau;
}
