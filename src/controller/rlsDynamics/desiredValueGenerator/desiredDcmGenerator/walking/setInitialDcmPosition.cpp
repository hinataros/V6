/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setInitialDcmPosition(const Vector3d &rX0)
{
  if(debug) DEBUG;

  this->rX0 = rX0;
}
