/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::eeWrenchRef(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info->treeModel[0].controlNodeNum);
  texMaker.setLimbNum(3, false);
  texMaker.setLimbNum(4, false);

  reset();
  setFileName("eeForceRef");

  setTimeDependentDat("fRef");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].controlNodeNum);
  gpMaker.setLimbNum(3, false);
  gpMaker.setLimbNum(4, false);
  gpMaker.setYLabel("EE force ref. [N]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeMomentRef");

  setTimeDependentDat("nRef");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].controlNodeNum);
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
