/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::rcMomRef(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("rcLinMomRef");
  makeDat("t-dpRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("R. C. lin. mom. ref. [N]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("rcAngMomRef");
  makeDat("t-dlCRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("R. C. ang. mom. ref. [Nm]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("rcSpatialMomRef");
  texMaker.setCaption("Rate of change of spatial momentum reference values.");
  texMaker.makeTex();
}
