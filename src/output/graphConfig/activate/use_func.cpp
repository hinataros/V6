/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::use_func(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  // index
  dcm(gpMaker, texMaker);
  sysMom(gpMaker, texMaker);
  localCop(gpMaker, texMaker);
  netCop(gpMaker, texMaker);
  stabilityIndex(gpMaker, texMaker);
}
