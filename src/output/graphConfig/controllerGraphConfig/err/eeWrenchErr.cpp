/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::eeWrenchErr(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.eeNum);

  reset();
  setFileName("eeForceErr");
  makeDat("t-ef");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.eeNum);
  gpMaker.setYLabel("EE force err. [N]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("eeMomentErr");
  makeDat("t-en");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.eeNum);
  gpMaker.setYLabel("EE moment err. [Nm]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("eeWrenchErr");
  texMaker.setCaption("End effector wrench error values.");
  texMaker.makeTex();
}
