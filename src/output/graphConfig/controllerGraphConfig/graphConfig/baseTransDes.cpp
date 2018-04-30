/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::baseTransDes(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("basePosDes");
  makeDat("t-rBDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base pos. [mm]");
  gpMaker.chUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseVelDes");
  makeDat("t-vBDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAccDes");
  makeDat("t-dvBDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base acc. [m/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("baseTransDes");
  texMaker.setCaption("Desired base translation values.");
  texMaker.makeTex();
}
