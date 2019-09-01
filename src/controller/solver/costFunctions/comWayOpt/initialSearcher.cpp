#include "config.hpp"
#include "common.hpp"

#include "walkingFunction.hpp"
#include "comWayOpt.hpp"


void RLS::comWayOpt::initialSearcher(int num, double *xRet, double inVal)
{
  if(CWO_DEBUG) DEBUG;

  for(int i=0; i<num; i++)
    xRet[i] = inVal;
}

void RLS::comWayOpt::initialSearcher(int num, double *xRet)
{
  if(CWO_DEBUG) DEBUG;

  for(int i=0; i<num; i++){
    if(i%2==0)
      xRet[i] = 0.3;
    else
      xRet[i] = 0.2;
  }
// o(num);
//   xRet[0] = 0.55;
//   xRet[1] = 0.25;
//   xRet[2] = 0.55;
//   xRet[3] = 0.25;
//   xRet[4] = 0.55;
//   xRet[5] = 0.25;
//   xRet[6] = 0.55;
//   xRet[7] = 0.25;
//   xRet[8] = 0.55;
//   xRet[9] = 0.25;
//   xRet[10] = 0.55;
//   xRet[11] = 0.25;
  // xRet[12] = 0.55;
  // xRet[13] = 0.25;
}
