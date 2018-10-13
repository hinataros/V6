/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::setInitialValue()
{
  if(debug) DEBUG;

  th0 = model->readJointStateVector("joint angle");

  rC0 = model->all.rC;
  rB0 = model->link[info->rootNode].r;
  xiB0 = R2xi(model->link[info->rootNode].R);

  rX0 = model->all.rC + sqrt(model->all.rC(2)/abs(worldModel->ag(2)))*model->all.vC;

  cal_X0 = model->readControlNodeValueVector("6D position");

  cal_FB0 <<
    model->link[info->rootNode].f,
    model->link[info->rootNode].n;
}
