/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::baseTransErr(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("basePosErr");
  makeDat("t-erB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base pos. err. [mm]");
  gpMaker.chUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseVelErr");
  makeDat("t-evB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base vel. err. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("baseTransErr");
  texMaker.setCaption("Base translation error values.");
  texMaker.makeTex();
}
