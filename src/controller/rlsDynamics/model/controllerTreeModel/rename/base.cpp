/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::base()
{
  if(debug) DEBUG;

  // inertia
  IB = model->all.M.block(3,3,3,3);
  MB = model->all.M.block(0,0,6,6);
  HBth = model->all.M.block(0,6,6,info->dof.joint);
  cal_AB = model->all.M.block(0,0,6,info->dof.all);

  Mth = model->all.M.block(6,6,info->dof.joint,info->dof.joint);

  // nonlinear
  cal_dAB = model->all.dM.block(0,0,6,info->dof.all);
  cal_CB = model->all.c.head(6);
  cal_GB = model->all.g.head(6);
  cth = model->all.c.tail(info->dof.joint);

  // gravity
  gth = model->all.g.tail(info->dof.joint);
}
