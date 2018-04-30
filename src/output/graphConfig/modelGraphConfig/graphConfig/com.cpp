/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::com(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("comPos");
  makeDat("t-rC");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CoM pos. [mm]");
  gpMaker.chUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("comVel");
  makeDat("t-vC");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CoM vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("com");
  texMaker.setCaption("CoM values.");
  texMaker.makeTex();
}
