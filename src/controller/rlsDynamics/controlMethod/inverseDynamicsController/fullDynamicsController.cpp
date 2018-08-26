/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::fullDynamicsController(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // momentum control
  (this->*momentumController_ptr)(info);

  // acceleration control
  (this->*motionController_ptr)(info);

  // force control
  (this->*forceController_ptr)(info);

  // torque control
  (this->*torqueController_ptr)(info);

  return tau;
}
