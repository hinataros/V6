/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::velocityOutputConfig(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // desired value
  dc_list.rBDes = rBDes;
  dc_list.vBDes = vBDes;

  dc_list.xiBDes = xiBDes;
  dc_list.wBDes = wBDes;

  // error value
  dc_list.erC = erC;
  dc_list.erB = erB;
  dc_list.eoB = eoB;

  dc_list.vBRef = vBRef;
  dc_list.wBRef = wBRef;
  dc_list.dthRef = dthRef;
}
