/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::baseRotErr(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("baseRotErr");
  makeDat("t-eoB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base orient. err. [deg]");
  gpMaker.setUnit("RAD2DEG");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAngVelErr");
  makeDat("t-ewB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base ang. vel. err. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("baseRotErr");
  texMaker.setCaption("Base rotation error values.");
  texMaker.makeTex();
}
