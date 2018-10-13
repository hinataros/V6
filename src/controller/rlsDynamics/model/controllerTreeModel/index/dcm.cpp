/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::dcm()
{
  if(debug) DEBUG;

  double g = 9.81;

  wX = sqrt(g/rC0(2));

  rX = model->all.rC + (model->all.vC/wX);
}
