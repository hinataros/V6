/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::state()
{
  if(debug) DEBUG;

  th = model->readJointStateVector("joint angle");
  dth = model->readJointStateVector("joint velocity");

  cal_X = model->readControlNodeValueVector("6D position");
  cal_V = model->readControlNodeValueVector("spatial velocity");
  cal_F = model->readControlNodeValueVector("wrench");

  cal_Xsensor = model->readSensorNodeValueVector("6D position");
  cal_Fsensor = model->readSensorNodeValueVector("force torque sensor");

  rB = model->link[info->rootNode].r;
  RB = model->link[info->rootNode].R;
  xiB = R2xi(model->link[info->rootNode].R);

  cal_XB <<
    rB,
    xiB;

  vB = model->link[info->rootNode].v;
  wB = model->link[info->rootNode].w;

  cal_VB <<
    vB,
    wB;

  dq <<
    cal_VB,
    dth;

  rC = model->all.rC;
  vC = model->all.vC;

  cal_VM <<
    vC,
    wB;

  dqM <<
    cal_VM,
    dth;

  cal_VC <<
    vC,
    wB + IC.inverse()*HC*dth;
}
