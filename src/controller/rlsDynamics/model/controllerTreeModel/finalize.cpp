/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::finalize()
{
  if(debug) DEBUG;

  delete[] r0;
  delete[] R0;

  delete[] r;
  delete[] R;

  delete[] rsensor;
}
