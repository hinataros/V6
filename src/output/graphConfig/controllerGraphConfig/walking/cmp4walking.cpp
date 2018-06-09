/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::cmp4walking(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  // double y_length = 31.5;
  // double x_length_top = 58;
  // double x_length_bottom = -40;
  double y_length = 21;
  double x_length_top = 116/3;
  double x_length_bottom = -80/3;

  texMaker.reset();

  reset();
  setFileName("cmpx");
  makeDat("t-rcmpx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CMP x [mm]");
  gpMaker.setUnit("m");
  gpMaker.add("set yrange[-60:80]");
  gpMaker.add("set object 1 rect from 0, "+to_string(x_length_bottom)+" to 1e+3, "+to_string(x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("cmpy");
  makeDat("t-rcmpy");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CMP y [mm]");
  gpMaker.setUnit("m");
  gpMaker.add("set yrange[-80:80]");
  gpMaker.add("set object 1 rect from 0, (39-"+to_string(y_length)+") to 1e+3, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.add("set object 2 rect from 0, (-39-"+to_string(y_length)+") to 1e+3, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("cmp");
  texMaker.setCaption("CMP values.");
  texMaker.makeTex();
}
