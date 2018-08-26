/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::accelerationOutputConfig(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // desired value
  dc_list.rBDes = rBDes;
  dc_list.vBDes = vBDes;
  dc_list.dvBDes = dvBDes;

  dc_list.xiBDes = xiBDes;
  dc_list.wBDes = wBDes;
  dc_list.dwBDes = dwBDes;

  // error value
  dc_list.erB = erB;
  dc_list.evB = evB;
  dc_list.eoB = eoB;
  dc_list.ewB = ewB;

  dc_list.dvBRef = dvBRef;
  dc_list.dwBRef = dwBRef;
  dc_list.ddthRef = ddthRef;
}
