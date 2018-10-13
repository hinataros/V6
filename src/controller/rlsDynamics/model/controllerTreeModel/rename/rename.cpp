/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::rename()
{
  if(debug) DEBUG;

  state();
  base();
  mix();
  centroidal();
  others();
}
