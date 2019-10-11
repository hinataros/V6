/**
   @author Ryotaro Hinata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::joint_wTorso3(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(5);

  reset();
  setFileName("jointAng");

  setTimeDependentDat("tree model th");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);

  gpMaker.setLimb(5);

  gpMaker.setDimention(1, 6);
  gpMaker.setDimention(2, 6);
  gpMaker.setDimention(3, 3);
  gpMaker.setDimention(4, 4);
  gpMaker.setDimention(5, 4);

  gpMaker.setYLabel("j. ang. [deg]");
  gpMaker.setUnit("RAD2DEG");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("jointVel");

  setTimeDependentDat("tree model dth");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);

  gpMaker.setLimb(5);

  gpMaker.setDimention(1, 6);
  gpMaker.setDimention(2, 6);
  gpMaker.setDimention(3, 3);
  gpMaker.setDimention(4, 4);
  gpMaker.setDimention(5, 4);

  gpMaker.setYLabel("j. vel. [rad/s]");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("joint");
  texMaker.setCaption("Joint values.");
  texMaker.makeTex();
}
