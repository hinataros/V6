/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::mixedQuasiAccOptRef(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("comAccOptRef");
  makeDat("t-dvCoptRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Optimized CoM acc. ref. [m/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAngAccOptRef");
  makeDat("t-dwBoptRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Optimized base ang. acc. ref. [rad/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("jointAccOptRef");
  makeDat("t-ddthoptRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  for(int i=1; i<info.value.joint+1; i++)
    gpMaker.setDimention(i, info.limb[i].dof);
  gpMaker.setYLabel("Optimized j. acc. ref. [rad/s^2]");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.setLimb(info.value.joint);
  texMaker.setNewline();
  texMaker.addMinipage();

  texMaker.setTexName("mixedQuasiAccOptRef");
  texMaker.setCaption("Non-iterative optimized Mixed quasi-acceleration reference values.");
  texMaker.makeTex();
}
