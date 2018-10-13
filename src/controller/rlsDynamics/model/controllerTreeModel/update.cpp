/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::update()
{
  if(debug) DEBUG;

  contactCoordinate();

  model->transformMatrix();
  // model.jacobian(rkk);

  transform();

  rename();

  index();
 }
