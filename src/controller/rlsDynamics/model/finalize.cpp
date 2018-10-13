/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerModel.hpp"

void RLS::ControllerModel::finalize()
{
  if(debug) DEBUG;

  delete[] treeModel;
}
