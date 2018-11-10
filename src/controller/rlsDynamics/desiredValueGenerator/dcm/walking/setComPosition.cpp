/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setComPosition(const Vector3d &rC0)
{
  if(debug) DEBUG;

  rCw0 = rC0;
}
