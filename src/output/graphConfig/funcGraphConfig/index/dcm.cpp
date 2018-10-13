/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::dcm(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("dcm");

  setVerticalDat("time");
  setHorizontalDat("rX");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("DCM pos. [mm]");
  gpMaker.setUnit("m");
  // gpMaker.add("set ytics 300");
  // gpMaker.add("set yrange[-30:750]");
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
