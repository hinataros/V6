#include "config.hpp"
#include "common.hpp"

#include "comWayOpt.hpp"


void RLS::comWayOpt::initialSearcher(double *xRet)
{
  for(int i=0; i<nparam; i++)
    xRet[i] = 0.2;
}
