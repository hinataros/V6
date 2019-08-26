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

  wXt = sqrt(g/rC(2)); // amiyata
  dwXt = -(vC(2)/(2.*rC(2))) * sqrt(g/rC(2)); // amiyata
  // o(vC(2));
  // o(dwXt);
  // gc;

  rX = model->all.rC + (model->all.vC/wX);
  rXt = model->all.rC + (model->all.vC/wXt);
}
