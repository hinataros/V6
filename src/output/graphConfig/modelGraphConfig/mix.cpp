/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::mix(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("comPos");
  makeDat("t-rC");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CoM pos. [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("comVel");
  makeDat("t-vC");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CoM vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseOrient");
  makeDat("t-xiB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base orient. [deg]");
  gpMaker.setUnit("RAD2DEG");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAngVel");
  makeDat("t-wB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base ang. vel. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("mix");
  texMaker.setCaption("Mixed quasi values.");
  texMaker.makeTex();
}
