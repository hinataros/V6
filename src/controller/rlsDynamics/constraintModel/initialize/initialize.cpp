/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::initialize(TreeModelInfo &info, const ControllerTreeModel &model)
{
  if(debug) DEBUG;

  setModel(info, model);

  initializeConstraintInfo();
  resize();
}
