/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::mixedQuasiAccRef(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  reset();
  setFileName("comAccRef");
  makeDat("t-dvCRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CoM acc. ref. [m/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAngAccRef");
  makeDat("t-dwBRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Base ang. acc. ref. [rad/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("jointAccRef");
  makeDat("t-ddthRef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  for(int i=1; i<info.value.joint+1; i++)
    gpMaker.setDimention(i, info.limb[i].dof);
  gpMaker.setYLabel("J. acc. ref. [rad/s^2]");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.setLimb(info.value.joint);
  texMaker.setNewline();
  texMaker.addMinipage();

  texMaker.setTexName("mixedQuasiAccRef");
  texMaker.setCaption("Mixed quasi-acceleration reference values.");
  texMaker.makeTex();
}
