/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

void RLS::Ext::setControllerMap(RlsDynamics *io)
{
  if(debug) DEBUG;

  o("hogehogehoge");
  gc;

  // // momentum controller
  // // ****************************************************************
  // map_momentumController["test"] = &RLS::RlsDynamics::testMomentumController;

  // // operational space reference
  // // ****************************************************************
  // map_operationalSpaceController["test"] = &RLS::RlsDynamics::testOperationalSpaceController;

  // // configuration space controller
  // // ****************************************************************
  // map_motionController["test"] = &RLS::RlsDynamics::testMotionControler;

  // // internal force controller
  // // ****************************************************************
  // map_internalForceController["test"] = &RLS::RlsDynamics::testInternalForceController;

  // // force controller
  // // ****************************************************************
  // map_forceController["test"] = &RLS::RlsDynamics::testForceController;

  // // torque controller
  // // ****************************************************************
  // map_torqueController["test"] = &RLS::RlsDynamics::testTorqueController;

  // inverse dynamics controller
  // ****************************************************************
  // io.map_inverseDynamicsController["test"] = &RLS::EXT::testInverseDynamicsController;
}
