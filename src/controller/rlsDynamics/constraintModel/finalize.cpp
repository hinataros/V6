/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::finalize()
{
  if(debug) DEBUG;

  delete[] info.constraint.c.controlNode;
  delete[] info.constraint.m.controlNode;
}
