/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::dcmDes(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("dcmPosDes");
  makeDat("t-rXDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. DCM [mm]");
  gpMaker.chUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("dcmVelDes");
  makeDat("t-drXDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. DCM vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("dcmDes");
  texMaker.setCaption("Desired DCM values.");
  texMaker.makeTex();
}
