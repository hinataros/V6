/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::baseTransDes(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("basePosDes");
  makeDat("t-rBDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base pos. [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseVelDes");
  makeDat("t-vBDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAccDes");
  makeDat("t-dvBDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base acc. [m/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("baseTransDes");
  texMaker.setCaption("Desired base translation values.");
  texMaker.makeTex();
}