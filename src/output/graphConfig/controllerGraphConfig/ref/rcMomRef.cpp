/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::rcMomRef(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

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
