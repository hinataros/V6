/**
   @author Ryotaro Hinata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::jointLimitGradient_wTorso3(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(5);

  reset();
  setFileName("jointLimitGradient");

  setTimeDependentDat("ext joint limit gradient");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);

  gpMaker.setLimb(5);

  gpMaker.setDimention(1, 6);
  gpMaker.setDimention(2, 6);
  gpMaker.setDimention(3, 3);
  gpMaker.setDimention(4, 4);
  gpMaker.setDimention(5, 4);

  // gpMaker.add("set yrange[0:1.4]");
  // gpMaker.add("set ytics 0.2");

  gpMaker.setYLabel("gradient [-]");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("jointGradient");
  texMaker.setCaption("Joint gradient values.");
  texMaker.makeTex();
}
