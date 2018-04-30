/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::eeTransDes(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("eePosDes");
  makeDat("t-rDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE des. pos. [mm]");
  gpMaker.chUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  reset();
  setFileName("eeVelDes");
  makeDat("t-vDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE des. vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  reset();
  setFileName("eeAccDes");
  makeDat("t-dvDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE des. acc. [m/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  texMaker.setTexName("eeTransDes");
  texMaker.setCaption("Desired end effector translation values.");
  texMaker.makeTex();
}
