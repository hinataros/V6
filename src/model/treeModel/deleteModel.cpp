/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::deleteModel()
{
  if(debug) DEBUG;

  delete[] link;

  delete[] info.controlNode;
  delete[] info.sensorNode;
}
