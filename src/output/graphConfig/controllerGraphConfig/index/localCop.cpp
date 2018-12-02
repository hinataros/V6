/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::localCop(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info->treeModel[0].sensorNodeNum);
  texMaker.setLimbNum(3, false);
  texMaker.setLimbNum(4, false);

  double y_length = 31.5;
  double x_length_top = 58;
  double x_length_bottom = -40;

  reset();
  setFileName("localCoPx");

  setTimeDependentDat("rpkx");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].sensorNodeNum);
  gpMaker.setLimbNum(3, false);
  gpMaker.setLimbNum(4, false);
  gpMaker.setYLabel("EE CoP x [mm]");
  gpMaker.setUnit("m");

  gpMaker.add(1,"set yrange[-60:80]");
  gpMaker.add(1,"set object 1 rect from 0, "+to_string(x_length_bottom)+" to 1e+3, "+to_string(x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.add(2,"set yrange[-60:80]");
  gpMaker.add(2,"set object 1 rect from 0, "+to_string(x_length_bottom)+" to 1e+3, "+to_string(x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("localCoPy");

  setTimeDependentDat("rpky");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info->treeModel[0].sensorNodeNum);
  gpMaker.setLimbNum(3, false);
  gpMaker.setLimbNum(4, false);
  gpMaker.setYLabel("EE CoP y [mm]");
  gpMaker.setUnit("m");
  gpMaker.add(1,"set yrange[-40:40]");

  gpMaker.add(1,"set object 1 rect from 0, (-"+to_string(y_length)+") to 1e+3, ("+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.add(2,"set yrange[-40:40]");
  gpMaker.add(2,"set object 1 rect from 0, (-"+to_string(y_length)+") to 1e+3, ("+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("localCoP");
  texMaker.setCaption("Local CoP values.");
  texMaker.makeTex();
}
