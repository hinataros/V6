/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::dcmErr(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("dcmErr");

  setVerticalDat("time");
  setHorizontalDat("eX");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("DCM err. [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("dcmErr");
  texMaker.setCaption("DCM error values.");
  texMaker.makeTex();
}
