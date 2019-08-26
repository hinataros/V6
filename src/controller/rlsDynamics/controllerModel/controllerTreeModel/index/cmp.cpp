/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::cmp()
{
  if(debug) DEBUG;

  Vector3d f = Vector3d::Zero();

  for(int i=0; i<info->controlNodeNum; i++)
    f += cal_F.segment((6*i), 3);

  if(f(2) != 0.)
    rcmp = rp - f.head(2)*model->all.rC(2)/f(2);
    // rcmp = rp + bb_Spx*dlCRef.head(2)/f(2);

  else
    rcmp = rp;
}
