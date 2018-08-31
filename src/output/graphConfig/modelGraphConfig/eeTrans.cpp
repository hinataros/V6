/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::eeTrans(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.eeNum);

  reset();
  setFileName("eePos");
  makeDat("t-r");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.eeNum);
  gpMaker.setYLabel("EE pos. [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeVel");
  makeDat("t-v");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.eeNum);
  gpMaker.setYLabel("EE vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeTrans");
  texMaker.setCaption("End effector translation values.");
  texMaker.makeTex();
}
