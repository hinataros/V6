/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::index()
{
  if(debug) DEBUG;

  cop();
  cmp();
  dcm();
}
