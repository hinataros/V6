/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

int RLS::Output::setPlane(string plane)
{
  if(plane=="x")
    return 1;
  else if(plane=="y")
    return 2;
  else if(plane=="z")
    return 3;
  else
    return -1;
}
