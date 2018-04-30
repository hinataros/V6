/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::comErr(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("comErr");
  makeDat("t-erC");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CoM pos. err. [mm]");
  gpMaker.chUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("comVelErr");
  makeDat("t-evC");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CoM vel. err. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("comErr");
  texMaker.setCaption("CoM error values.");
  texMaker.makeTex();
}
