/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setModel(const ControllerTreeModel &model)
{
  if(debug) DEBUG;

  this->model = &model;
}
