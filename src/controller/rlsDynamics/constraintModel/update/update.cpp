/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::update()
{
  if(debug) DEBUG;

  decompose();
  objective();
  rename();
}
