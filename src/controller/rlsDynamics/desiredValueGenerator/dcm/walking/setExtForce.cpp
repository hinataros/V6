/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setExtForce(const Vector3d &fext)
{
  this->fext = fext;
}

