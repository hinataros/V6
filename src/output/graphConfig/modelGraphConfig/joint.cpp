/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::joint(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  // texMaker.reset();
  // texMaker.setLimb(info.controlNodeNum);

  // reset();
  // setFileName("jointAng");
  // makeDat("t-th");

  // gpMaker.reset();
  // gpMaker.setName(file_name);
  // gpMaker.setLimb(info.controlNodeNum);
  // for(int i=1; i<info.controlNodeNum+1; i++)
  //   gpMaker.setDimention(i, info.limb[i].dof);
  // gpMaker.setYLabel("j. ang. [deg]");
  // gpMaker.setUnit("RAD2DEG");
  // gpMaker.makeGp();

  // texMaker.setName(file_name);
  // texMaker.addMinipage();

  // reset();
  // setFileName("jointVel");
  // makeDat("t-dth");

  // gpMaker.reset();
  // gpMaker.setName(file_name);
  // gpMaker.setLimb(info.controlNodeNum);
  // for(int i=1; i<info.controlNodeNum+1; i++)
  //   gpMaker.setDimention(i, info.limb[i].dof);
  // gpMaker.setYLabel("j. vel. [rad/s]");
  // gpMaker.makeGp();

  // texMaker.setName(file_name);
  // texMaker.addMinipage();

  // texMaker.setTexName("joint");
  // texMaker.setCaption("Joint values.");
  // texMaker.makeTex();
}
