/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::baseRotDes(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("baseOrientDes");
  makeDat("t-xiBDes");

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
  makeDat("t-wBDes");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Des. base ang. vel. [rad/s]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("baseAngAccDes");
  makeDat("t-dwBDes");

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
