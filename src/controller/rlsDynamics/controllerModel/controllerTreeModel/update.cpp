/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::update()
{
  if(debug) DEBUG;

  VectorXd zVec = VectorXd::Zero(3*info->controlNodeNum);
  update(zVec);
}

// amiyata rkk
void RLS::ControllerTreeModel::update(VectorXd &offset)
{
  if(debug) DEBUG;

  contactCoordinate();

  // model->transformMatrix();
  model->transformMatrix(offset);
  // model.jacobian(rkk);

  transform();

  rename();

  index();
}
