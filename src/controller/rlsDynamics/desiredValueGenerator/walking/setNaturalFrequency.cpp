/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setNaturalFrequency(const double &wX)
{
  if(debug) DEBUG;

  this->wX = wX;
}
