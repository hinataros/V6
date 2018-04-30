/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::eeRotDes(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("eeOrientDes");
  makeDat("t-xiDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE des. orient. [deg]");
  gpMaker.chUnit("RAD2DEG");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  reset();
  setFileName("eeAngVelDes");
  makeDat("t-wDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE des. ang. vel. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  reset();
  setFileName("eeAngAccDes");
  makeDat("t-dwDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE des. ang. acc. [rad/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  texMaker.setTexName("eeRotDes");
  texMaker.setCaption("Desired end effector rotation values.");
  texMaker.makeTex();
}
