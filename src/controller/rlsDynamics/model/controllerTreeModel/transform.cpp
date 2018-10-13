/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::transform()
{
  if(debug) DEBUG;

  bb_TB2k = model->all.TB2k;
  bb_dTB2k = model->all.dTB2k;

  bb_TC2k = model->all.TC2k;
  bb_dTC2k = model->all.dTC2k;

  cal_J = model->all.J;
  cal_dJ = model->all.dJ;
}
