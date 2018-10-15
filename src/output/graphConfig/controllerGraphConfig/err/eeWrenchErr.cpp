/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::eeWrenchErr(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info->treeModel[0].controlNodeNum);

  reset();
  setFileName("eeForceErr");

  setVerticalDat("time");
  setHorizontalDat("ef");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].controlNodeNum);
  gpMaker.setYLabel("EE force err. [N]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeMomentErr");

  setVerticalDat("time");
  setHorizontalDat("en");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].controlNodeNum);
  gpMaker.setYLabel("EE moment err. [Nm]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeWrenchErr");
  texMaker.setCaption("End effector wrench error values.");
  texMaker.makeTex();
}
