/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::finalize()
{
  if(debug) DEBUG;

  delete[] link;
}
