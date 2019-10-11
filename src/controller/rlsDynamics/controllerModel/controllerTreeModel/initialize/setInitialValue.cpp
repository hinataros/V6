/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::setInitialValue()
{
  if(debug) DEBUG;

  th0 = model->readJointState("joint angle");

  rB0 = model->link[info->rootNode].r;
  RB0 = model->link[info->rootNode].R;

  for(int i=0; i<info->controlNodeNum; i++){
    r0[i] = model->readControlNodeValue<Vector3d>(i,"position");
    R0[i] = model->readControlNodeValue<Matrix3d>(i,"orientation");
  }

  rC0 = model->all.rC;
  rX0 = model->all.rC + sqrt(model->all.rC(2)/abs(worldModel->ag(2)))*model->all.vC;

  cal_FB0 <<
    model->link[info->rootNode].f,
    model->link[info->rootNode].n;

  // joint limit (2019/10/3 hinata)

  thMax = model->readJointState("maximum joint angle");
  thMin = model->readJointState("minimum joint angle");
  thMid = 0.5 * (thMax + thMin);
}
