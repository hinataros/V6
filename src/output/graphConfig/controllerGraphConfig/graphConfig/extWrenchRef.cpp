/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::extWrenchRef(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("extForceRef");
  makeDat("t-fextRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("External force ref. [N]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("extMomentRef");
  makeDat("t-nextRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("External moment ref. [N/m]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("extWrenchRef");
  texMaker.setCaption("External wrench reference values.");
  texMaker.makeTex();
}
