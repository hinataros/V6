/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameDebug(Model &model)
{
  if(debug) DEBUG;

  // o(cth);
  // o(model.hoap2.all.dM.block(6,6,info.dof.joint,info.dof.joint)*model.hoap2.all.dth);

  // o(cth- model.hoap2.all.dM.block(6,6,info.dof.joint,info.dof.joint)*model.hoap2.all.dth);

  // // o(dHC.transpose()*cal_VM.tail(3) + model.hoap2.all.dMM.block(6,6,info.dof.joint,info.dof.joint)*model.hoap2.all.dth);

  // // o(cthC - (dHC.transpose()*cal_VM.tail(3) + model.hoap2.all.dMM.block(6,6,info.dof.joint,info.dof.joint)*model.hoap2.all.dth));
  // gc;

  // o(cal_CB);
  // Vector3d cBm = model.hoap2.all.dM.block(3,0,3,info.dof.all)*dq + model.hoap2.all.m*cross(drB2C).transpose()*cal_VM.head(3);
  // o(cBm);
  // o(cal_CB.tail(3) - cBm);
  // gc;

  // Vector6d cal_CBtemp = Vector6d::Zero();
  // Vector3d temp = model.hoap2.all.m*cross(drB2C).transpose()*cal_VM.tail(3) + model.hoap2.all.m*model.hoap2.all.dJB2C*model.hoap2.all.dth;
  // cal_CBtemp.head(3) = temp;
  // cal_CBtemp.tail(3) = (dIC + model.hoap2.all.m*cross(rB2C)*(cross(drB2C).transpose()))*cal_VM.tail(3) + (dHC + model.hoap2.all.m*cross(rB2C)*model.hoap2.all.dJB2C)*model.hoap2.all.dth;
  // cal_CBtemp.tail(3) = dIC*cal_VM.tail(3) + dHC*model.hoap2.all.dth + cross(rB2C)*temp;
  // cal_CBtemp.tail(3) = -model.hoap2.all.m*cross(rB2C).transpose()*cal_VB.head(3) + dIB*cal_VM.tail(3) + dHB*model.hoap2.all.dth;

  // o(cal_CBtemp);
  // o(cal_CB - cal_CBtemp);
  // gc;
  // Vector6d cal_CMtemp = Vector6d::Zero();
  // cal_CMtemp <<
  //   cal_CB.head(3) + model.hoap2.all.m*cross(drB2C)*cal_VM.tail(3) - model.hoap2.all.m*model.hoap2.all.dJB2C*model.hoap2.all.dth,
  //   -cross(rB2C)*cal_CB.head(3) + cal_CB.tail(3);

  // Vector6d cal_CMtemptemp = Vector6d::Zero();
  // cal_CMtemptemp <<
  //   Vector3d::Zero(),
  //   dIC*cal_VM.tail(3) + dHC*model.hoap2.all.dth;


  // o(cal_CMtemp);
  // o(cal_CMtemptemp);
  // o(cal_CMtemp - cal_CMtemptemp);
}
