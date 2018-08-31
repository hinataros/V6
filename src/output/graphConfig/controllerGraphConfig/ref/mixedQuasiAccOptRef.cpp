/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::mixedQuasiAccOptRef(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  // texMaker.reset();

  // reset();
  // setFileName("comAccOptRef");
  // makeDat("t-dvCoptRef");

  // gpMaker.reset();
  // gpMaker.setName(file_name);
  // gpMaker.setYLabel("Optimized CoM acc. ref. [m/s^2]");
  // gpMaker.setDimention(3);
  // gpMaker.makeGp();

  // texMaker.setName(file_name);
  // texMaker.addMinipage();

  // reset();
  // setFileName("baseAngAccOptRef");
  // makeDat("t-dwBoptRef");

  // gpMaker.reset();
  // gpMaker.setName(file_name);
  // gpMaker.setYLabel("Optimized base ang. acc. ref. [rad/s^2]");
  // gpMaker.setDimention(3);
  // gpMaker.makeGp();

  // texMaker.setName(file_name);
  // texMaker.addMinipage();

  // reset();
  // setFileName("jointAccOptRef");
  // makeDat("t-ddthoptRef");

  // gpMaker.reset();
  // gpMaker.setName(file_name);
  // gpMaker.setLimb(info.eeNum);
  // for(int i=1; i<info.eeNum+1; i++)
  //   gpMaker.setDimention(i, info.limb[i].dof);
  // gpMaker.setYLabel("Optimized j. acc. ref. [rad/s^2]");
  // gpMaker.makeGp();

  // texMaker.setName(file_name);
  // texMaker.setLimb(info.eeNum);
  // texMaker.setNewline();
  // texMaker.addMinipage();

  // texMaker.setTexName("mixedQuasiAccOptRef");
  // texMaker.setCaption("Non-iterative optimized Mixed quasi-acceleration reference values.");
  // texMaker.makeTex();
}
