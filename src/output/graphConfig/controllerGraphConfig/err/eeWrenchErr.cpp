/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::eeWrenchErr(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.value.joint);

  reset();
  setFileName("eeForceErr");
  makeDat("t-ef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE force err. [N]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeMomentErr");
  makeDat("t-en");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE moment err. [Nm]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeWrenchErr");
  texMaker.setCaption("End effector wrench error values.");
  texMaker.makeTex();
}
