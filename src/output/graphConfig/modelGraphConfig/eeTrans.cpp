/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::eeTrans(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info->treeModel[0].controlNodeNum);

  reset();
  setFileName("eePos");

  setTimeDependentDat("tree model r");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].controlNodeNum);
  gpMaker.setYLabel("EE pos. [mm]");
  gpMaker.setUnit("m");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeVel");

  setTimeDependentDat("tree model v");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].controlNodeNum);
  gpMaker.setYLabel("EE vel. [m/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeTrans");
  texMaker.setCaption("End effector translation values.");
  texMaker.makeTex();
}
