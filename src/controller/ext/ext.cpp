/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

void RLS::Ext::initialize(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->ext_momentumController_map["test"] = &RLS::Ext::testMomentumController;
  io->ext_motionController_map["test"] = &RLS::Ext::testMotionController;
  io->ext_forceController_map["test"] = &RLS::Ext::testForceController;
  io->ext_torqueController_map["test"] = &RLS::Ext::testTorqueController;
  io->ext_inverseDynamicsController_map["test"] = &RLS::Ext::testInverseDynamicsController;

  tw0 = 0.;
  des = Vector3d::Zero();

  hoge0 = Vector3d::Zero();
  hogepreDes = Vector3d::Zero();
  hogef = Vector3d::Zero();

  hogeDes = Vector3d::Zero();
  dhogeDes = Vector3d::Zero();
  ddhogeDes = Vector3d::Zero();
}

void RLS::Ext::reset(RlsDynamics *io, const double &t)
{
  tw0 = t;
  hogepreDes = hogef;
}

void RLS::Ext::readController(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->yamlInfo.checkValue<Vector3d>(hogef, "hogef");
  io->yamlInfo.checkValue<double>(twf, "twf");
}

void RLS::Ext::reconfigure(RlsDynamics *io)
{
  if(debug) DEBUG;

}

void RLS::Ext::every(RlsDynamics *io, const double &t)
{
  if(debug) DEBUG;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-tw0, twf, hogepreDes(i), hogef(i));

    hogeDes(i) = des(0) + hoge0(i);
    dhogeDes(i) = des(1);
    ddhogeDes(i) = des(2);
  }
}

void RLS::Ext::output(RlsDynamics *io)
{
  if(debug) DEBUG;

  outputList.hogeDes = hogeDes;
}

void RLS::Ext::finalize(RlsDynamics *io)
{
  if(debug) DEBUG;

}
