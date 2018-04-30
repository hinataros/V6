/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::joint(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("jointAng");
  makeDat("t-th");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  for(int i=1; i<info.value.joint+1; i++)
    gpMaker.setDimention(i, info.limb[i].dof);
  gpMaker.setYLabel("j. ang. [deg]");
  gpMaker.chUnit("RAD2DEG");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  reset();
  setFileName("jointVel");
  makeDat("t-dth");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  for(int i=1; i<info.value.joint+1; i++)
    gpMaker.setDimention(i, info.limb[i].dof);
  gpMaker.setYLabel("j. vel. [rad/s]");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  texMaker.setTexName("joint");
  texMaker.setCaption("Joint values.");
  texMaker.makeTex();
}
