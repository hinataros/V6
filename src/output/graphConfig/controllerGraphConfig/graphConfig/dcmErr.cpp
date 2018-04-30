/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::dcmErr(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("dcmErr");
  makeDat("t-eX");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("DCM err. [mm]");
  gpMaker.chUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("dcmErr");
  texMaker.setCaption("DCM error values.");
  texMaker.makeTex();
}
