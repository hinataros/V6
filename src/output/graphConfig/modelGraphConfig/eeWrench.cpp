/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::eeWrench(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.controlNodeNum);

  reset();
  setFileName("eeForce");
  makeDat("t-f");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.controlNodeNum);
  gpMaker.setYLabel("EE force [N]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeMoment");
  makeDat("t-n");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.controlNodeNum);
  gpMaker.setYLabel("EE moment [Nm]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeWrench");
  texMaker.setCaption("End effector wrench values.");
  texMaker.makeTex();
}
