/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::spatialMom(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("linMom");
  makeDat("t-p");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Lin. mom. [Ns]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("angMom");
  makeDat("t-lC");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Ang. mom. [Nms]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("spatialMom");
  texMaker.setCaption("Linear and angular momentum.");
  texMaker.makeTex();
}
