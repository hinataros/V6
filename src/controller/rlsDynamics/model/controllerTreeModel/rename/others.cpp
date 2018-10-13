/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::others()
{
  if(debug) DEBUG;

  M = model->all.m;

  rB2C = rC - rB;
  drB2C = vC - vB;

  JB2C = model->all.JB2C;
  dJB2C = model->all.dJB2C;
}
