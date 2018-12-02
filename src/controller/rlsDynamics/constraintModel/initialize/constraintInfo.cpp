/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::initializeConstraintInfo()
{
  if(debug) DEBUG;

  info.constraint.c.all = info.constraint.m.all = 0;

  for(int i=0; i<6; i++)
    info.constraint.c.axis[i] = info.constraint.m.axis[i] = 0;

  info.constraint.c.controlNode = new int[info.model->controlNodeNum];
  info.constraint.m.controlNode = new int[info.model->controlNodeNum];

  for(int i=0; i<info.model->controlNodeNum; i++)
    info.constraint.c.controlNode[i] = info.constraint.m.controlNode[i] = 0;
}
