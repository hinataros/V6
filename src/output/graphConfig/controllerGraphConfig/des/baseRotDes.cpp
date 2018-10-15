/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::baseRotDes(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("baseOrientDes");

  setVerticalDat("time");
  setHorizontalDat("xiBDes");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base orient. [deg]");
  gpMaker.setUnit("RAD2DEG");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAngVelDes");

  setVerticalDat("time");
  setHorizontalDat("wBDes");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base ang. vel. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAngAccDes");

  setVerticalDat("time");
  setHorizontalDat("dwBDes");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base ang. acc. [rad/s^2]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("baseRotDes");
  texMaker.setCaption("Desired base rotation values.");
  texMaker.makeTex();
}
