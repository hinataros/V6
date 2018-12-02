/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::eeRotErr(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info->treeModel[0].controlNodeNum);

  reset();
  setFileName("eeOrientErr");

  setTimeDependentDat("eo");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].controlNodeNum);
  gpMaker.setYLabel("EE orient. err. [rad]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeAngVelErr");

  setTimeDependentDat("ew");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].controlNodeNum);
  gpMaker.setYLabel("EE ang. vel. err. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeRotErr");
  texMaker.setCaption("End effector rotation error values.");
  texMaker.makeTex();
}
