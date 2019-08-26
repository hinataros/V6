/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"


void RLS::Walking::initialize()
{
  if(debug) DEBUG;

  // resize();
  readController(); // amiyata
  resetMat();
}
