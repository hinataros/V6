/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::eeRot(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.eeNum);

  reset();
  setFileName("eeOrient");
  makeDat("t-xi");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.eeNum);
  gpMaker.setYLabel("EE orient. [deg]");
  gpMaker.setUnit("RAD2DEG");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeAngVel");
  makeDat("t-w");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.eeNum);
  gpMaker.setYLabel("EE ang. vel. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeRot");
  texMaker.setCaption("End effector rotation values.");
  texMaker.makeTex();
}
