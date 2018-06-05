/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::comDes(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("comPosDes");
  makeDat("t-rCDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. CoM pos. [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("comVelDes");
  makeDat("t-vCDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. CoM vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("comAccDes");
  makeDat("t-dvCDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. CoM acc. [m/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("comDes");
  texMaker.setCaption("Desired CoM values.");
  texMaker.makeTex();
}
