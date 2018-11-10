/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::state()
{
  if(debug) DEBUG;

  th = model->readJointState("joint angle");
  dth = model->readJointState("joint velocity");

  for(int i=0; i<info->controlNodeNum; i++){
    r[i] = model->readControlNodeValue<Vector3d>(i, "position");
    R[i] = model->readControlNodeValue<Matrix3d>(i, "orientation");
  }

  cal_V = model->readControlNodeValue("spatial velocity");
  cal_F = model->readControlNodeValue("wrench");

  for(int i=0; i<info->sensorNodeNum; i++){
    rsensor[i] = model->readSensorNodeValue<Vector3d>(i, "position");
  }

  cal_Fsensor = model->readSensorNodeValue("force torque sensor");

  rB = model->link[info->rootNode].r;
  RB = model->link[info->rootNode].R;

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
