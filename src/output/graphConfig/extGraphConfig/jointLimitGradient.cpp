/**
   @author Ryotaro Hinata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::jointLimitGradient(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(4);

  reset();
  setFileName("jointLimitGradient");

  setTimeDependentDat("ext joint limit gradient");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);

  gpMaker.setLimb(4);

  gpMaker.setDimention(1, 6);
  gpMaker.setDimention(2, 6);
  gpMaker.setDimention(3, 4);
  gpMaker.setDimention(4, 4);

  gpMaker.add("set yrange[-1.5:1]");

  gpMaker.setYLabel("gradient [-]");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("jointGradient");
  texMaker.setCaption("Joint gradient values.");
  texMaker.makeTex();
}
