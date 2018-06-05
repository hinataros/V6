/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::eeWrenchRef(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.value.joint);
  texMaker.setLimbNum(3, false);
  texMaker.setLimbNum(4, false);

  reset();
  setFileName("eeForceRef");
  makeDat("t-fRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setLimbNum(3, false);
  gpMaker.setLimbNum(4, false);
  gpMaker.setYLabel("EE force ref. [N]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeMomentRef");
  makeDat("t-nRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setLimbNum(3, false);
  gpMaker.setLimbNum(4, false);
  gpMaker.setYLabel("EE moment ref. [Nm]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeWrenchRef");
  texMaker.setCaption("End effector wrench reference values.");
  texMaker.makeTex();
}
