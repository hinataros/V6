/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::baseTrans(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("basePos");
  makeDat("t-rB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base pos. [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseVel");
  makeDat("t-vB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("baseTrans");
  texMaker.setCaption("Base translation values.");
  texMaker.makeTex();
}
