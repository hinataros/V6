/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::baseTrans(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("basePos");
  makeDat("t-rB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base pos. [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseVel");
  makeDat("t-vB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("baseTrans");
  texMaker.setCaption("Base translation values.");
  texMaker.makeTex();
}
