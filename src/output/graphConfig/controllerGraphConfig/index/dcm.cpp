/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::dcm(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("dcm");
  makeDat("t-dcm");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("DCM [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("dcm");
  texMaker.setCaption("DCM values.");
  texMaker.makeTex();
}
