/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

void RLS::Ext::initialize(RlsDynamics *io)
{
  if(debug) DEBUG;

  // ext momentum
  // ****************************************************************
  io->ext_momentumController_map["default"] = &RLS::Ext::defaultController;
  io->ext_momentumController_map["linear_CRB"] = &RLS::Ext::linear_CRB;
  io->ext_momentumController_map["linear_Damper"] = &RLS::Ext::linear_Damper;
  io->ext_momentumController_map["linear_RNS"] = &RLS::Ext::linear_RNS;
  io->ext_momentumController_map["linear_MobilityCompensation"] = &RLS::Ext::linear_MobilityCompensation;
  io->ext_momentumController_map["linear_FrictionDistribution"] = &RLS::Ext::linear_FrictionDistribution;
  io->ext_momentumController_map["vrp_CRB"] = &RLS::Ext::vrp_CRB;
  io->ext_momentumController_map["vrp_Damper"] = &RLS::Ext::vrp_Damper;
  io->ext_momentumController_map["vrp_RNS"] = &RLS::Ext::vrp_RNS;
  io->ext_momentumController_map["vrp_MobilityCompensation"] = &RLS::Ext::vrp_MobilityCompensation;
  io->ext_momentumController_map["vrp_FrictionDistribution"] = &RLS::Ext::vrp_FrictionDistribution;
  io->ext_momentumController_map["vrp_FrictionDistribution_zDamper"] = &RLS::Ext::vrp_FrictionDistribution_zDamper;
  io->ext_momentumController_map["vrp_FrictionDistribution_zRNS"] = &RLS::Ext::vrp_FrictionDistribution_zRNS;

  // ext motion
  // ****************************************************************
  io->ext_motionController_map["default"] = &RLS::Ext::defaultConfigurationController;
  io->ext_motionController_map["relativeAngularAcceleration"] = &RLS::Ext::relativeAngularAcceleration;
  io->ext_motionController_map["RAA_noDistribution"] = &RLS::Ext::RAA_noDistribution;
  io->ext_motionController_map["RAA_fullBase"] = &RLS::Ext::RAA_fullBase;
  io->ext_motionController_map["RAA_partialBase"] = &RLS::Ext::RAA_partialBase;
  io->ext_motionController_map["RAA_RNS"] = &RLS::Ext::RAA_RNS;
  io->ext_motionController_map["relativeAngularVelocity"] = &RLS::Ext::relativeAngularVelocity;
  io->ext_motionController_map["RAV_noDistribution"] = &RLS::Ext::RAV_noDistribution;
  io->ext_motionController_map["RAV_fullBase"] = &RLS::Ext::RAV_fullBase;
  io->ext_motionController_map["RAV_partialBase"] = &RLS::Ext::RAV_partialBase;
  io->ext_motionController_map["RAV_noBase"] = &RLS::Ext::RAV_noBase;
  io->ext_motionController_map["SparseRAV_noDistribution"] = &RLS::Ext::RAV_noDistribution;
  io->ext_motionController_map["resolvedMomentumControl"] = &RLS::Ext::resolvedMomentumControl;

  // ext force
  // ****************************************************************
  io->ext_forceController_map["default"] = &RLS::Ext::defaultController;
  io->ext_forceController_map["copDistribution"] = &RLS::Ext::copDistribution;

  // ext torque
  // ****************************************************************
  io->ext_torqueController_map["default"] = &RLS::Ext::defaultController;

  // ext inverse dynamics
  // ****************************************************************
  io->ext_inverseDynamicsController_map["default"] = &RLS::Ext::defaultJointController;

  // ext external wrench
  // ****************************************************************
  io->ext_externalWrenchController_map["default"] = &RLS::Ext::defaultController;


  h = VectorXd::Zero(io->info.model.dof.joint);
  h2 = VectorXd::Zero(io->info.model.dof.joint);
  h3 = VectorXd::Zero(io->info.model.dof.joint);

  pMinus = VectorXd::Zero(io->info.model.dof.joint);
  pPlus = VectorXd::Zero(io->info.model.dof.joint);
  
  Jw = MatrixXd::Zero(3, io->info.model.dof.joint);
  dJw = MatrixXd::Zero(3, io->info.model.dof.joint);

  cal_JthM = MatrixXd::Zero(6, io->info.model.dof.joint);
  cal_dJthM = MatrixXd::Zero(6, io->info.model.dof.joint);

  W = MatrixXd::Identity(6,6);
  dW = MatrixXd::Zero(6,6);
  cal_VMRefBar = VectorXd::Zero(6);
  cal_dVMRefBar = VectorXd::Zero(6);

  dthMax = VectorXd::Zero(io->info.model.dof.joint);
  dthMin = VectorXd::Zero(io->info.model.dof.joint);

  wC = VectorXd::Zero(3);

  wCRef = VectorXd::Zero(3);
  dwCRef = VectorXd::Zero(3);
  DwRef = VectorXd::Zero(3);
  dDwRef = VectorXd::Zero(3);

  KpwBinit = Matrix3d::Zero();
  KdwBinit = Matrix3d::Zero();

  impact = false;
  reflex = false;

}

void RLS::Ext::reset(RlsDynamics *io, const double &t)
{
  if(debug) DEBUG;

}

void RLS::Ext::readController(RlsDynamics *io)
{
  if(debug) DEBUG;

}

void RLS::Ext::reconfigure(RlsDynamics *io)
{
  if(debug) DEBUG;

}

void RLS::Ext::every(RlsDynamics *io, const double &t)
{
  if(debug) DEBUG;

  Jw = io->model->IC.inverse() * io->model->HC;
  dJw = io->model->IC.inverse()*io->model->dHC
    - io->model->IC.inverse()*io->model->dIC*io->model->IC.inverse()*io->model->HC;
  // d(IC^-1)/dt = - IC^-1 * dIC * IC^-1
  cal_JthM.block(3,0,3,io->info.model.dof.joint) = Jw;
  cal_dJthM.block(3,0,3,io->info.model.dof.joint) = dJw;

  wC = io->model->wB + Jw*io->model->dth;


  double angleMargine = 5.0*DEG2RAD;

  for(int i=0; i<io->info.model.dof.joint; i++)
    h(i) = abs(io->model->th(i) - io->model->thMid(i))/(io->model->thMax(i) - io->model->thMid(i));
  
  for(int i=0; i<io->info.model.dof.joint; i++){
    if(io->model->th(i) >= io->model->thMax(i) - angleMargine){
      h2(i) = pow( (io->model->thMax(i) - angleMargine) - (io->model->thMin(i) +angleMargine),2) * (2*io->model->th(i) - (io->model->thMax(i) - angleMargine) - (io->model->thMin(i) +angleMargine)) / 0;
    }
    else if(io->model->th(i) <= io->model->thMin(i) + angleMargine){
      h2(i) = pow( (io->model->thMax(i) - angleMargine) - (io->model->thMin(i) +angleMargine),2) * (2*io->model->th(i) - (io->model->thMax(i) - angleMargine) - (io->model->thMin(i) +angleMargine)) / 0;
    }
    else{
      h2(i) = pow( (io->model->thMax(i) - angleMargine) - (io->model->thMin(i) +angleMargine),2) * (2*io->model->th(i) - (io->model->thMax(i) - angleMargine) - (io->model->thMin(i) +angleMargine)) /
        (4 * pow( (io->model->thMax(i) - angleMargine) - io->model->th(i),2) * pow(io->model->th(i) - (io->model->thMin(i) + angleMargine),2));
    }
  }

  VectorXd activateRange = VectorXd::Zero(io->info.model.dof.joint);
  for(int i=0; i<io->info.model.dof.joint; i++){
    activateRange(i) = (io->model->thMax(i) - io->model->thMin(i))/4;

    if(io->model->th(i) >= io->model->thMax(i)-angleMargine)
      h3(i) = 2*pow(activateRange(i), 2) / 0;

    else if(io->model->th(i) < io->model->thMax(i)-angleMargine && io->model->th(i) >= io->model->thMax(i)-activateRange(i))
      h3(i) = 2*pow(activateRange(i), 2) / pow((io->model->thMax(i)-angleMargine - io->model->th(i)), 3);

    else if(io->model->th(i) < io->model->thMax(i)-activateRange(i) && io->model->th(i) > io->model->thMin(i)+activateRange(i))
      h3(i) = 1;

    else if(io->model->th(i) <= io->model->thMin(i)+activateRange(i) && io->model->th(i) > io->model->thMin(i)+angleMargine)
      h3(i) = 2*pow(activateRange(i), 2) / pow(io->model->th(i) - io->model->thMin(i)+angleMargine, 3);

    else if(io->model->th(i) <= io->model->thMin(i)+angleMargine)
      h3(i) = 2*pow(activateRange(i), 2) / 0;
  }

  for(int i=0; i<io->info.model.dof.joint; i++){
    dthMax(i) = (io->model->thMax(i) - io->model->th(i))/io->worldModel->dt;
    dthMin(i) = (io->model->thMin(i) - io->model->th(i))/io->worldModel->dt;

    if(dthMax(i) > 5.4)
      dthMax(i) = 5.4;
    if(dthMin(i) < -5.4)
      dthMin(i) = -5.4;
  }

  // constraintCheck(io);
  baseOfSupport(io);

  // rootLinkManipulability(io);

  // gainSchedule(io, t);

}

void RLS::Ext::finalize(RlsDynamics *io)
{
  if(debug) DEBUG;

  bg::clear(BoS);
  bg::clear(Foot[0]);
  bg::clear(Foot[1]);

}
