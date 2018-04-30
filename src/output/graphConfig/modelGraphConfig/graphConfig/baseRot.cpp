/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::baseRot(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("baseOrient");
  makeDat("t-xiB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base orient. [deg]");
  gpMaker.chUnit("RAD2DEG");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAngVel");
  makeDat("t-wB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base ang. vel. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("baseRot");
  texMaker.setCaption("Base rotation values.");
  texMaker.makeTex();
}
