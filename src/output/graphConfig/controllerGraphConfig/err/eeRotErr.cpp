/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::eeRotErr(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.value.joint);

  reset();
  setFileName("eeOrientErr");
  makeDat("t-eo");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE orient. err. [rad]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeAngVelErr");
  makeDat("t-ew");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE ang. vel. err. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeRotErr");
  texMaker.setCaption("End effector rotation error values.");
  texMaker.makeTex();
}
