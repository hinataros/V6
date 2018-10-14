/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

VectorXd RLS::Ext::testInverseDynamicsController(RlsDynamics *io)
{
  if(debug) DEBUG;

  // // momentum control
  // (this->*momentumController_ptr)(io);

  // // motion control
  // (this->*motionController_ptr)(io);

  // // force control
  // (this->*forceController_ptr)(io);

  // // torque control
  // (this->*torqueController_ptr)(io);

  return io->tau;
}
