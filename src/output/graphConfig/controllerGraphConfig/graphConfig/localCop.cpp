/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::localCop(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  double y_length = 31.5;
  double x_length_top = 58;
  double x_length_bottom = -40;

  reset();
  setFileName("localCoPx");
  makeDat("t-rpkx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE CoP x [mm]");
  gpMaker.chUnit("m");

  gpMaker.add(1,"set yrange[-60:80]");
  gpMaker.add(1,"set object 1 rect from 0, "+to_string(x_length_bottom)+" to 1e+3, "+to_string(x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.add(2,"set yrange[-60:80]");
  gpMaker.add(2,"set object 1 rect from 0, "+to_string(x_length_bottom)+" to 1e+3, "+to_string(x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  reset();
  setFileName("localCoPy");
  makeDat("t-rpky");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE CoP y [mm]");
  gpMaker.chUnit("m");
  gpMaker.add(1,"set yrange[-80:0]");
  gpMaker.add(1,"set object 1 rect from 0, (-39-"+to_string(y_length)+") to 1e+3, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.add(2,"set yrange[0:80]");
  gpMaker.add(2,"set object 1 rect from 0, (39-"+to_string(y_length)+") to 1e+3, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  reset();
  setFileName("localCoPx-y");
  makeDat("rpky-rpkx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setXLabel("EE local CoP y [mm]");
  gpMaker.setYLabel("EE local CoP x [mm]");
  gpMaker.chUnit("m");

  gpMaker.add(1,"YLABEL_OFFSET_X = -0.9");
  gpMaker.add(1,"set xtics 40");
  gpMaker.add(1,"set parametric");
  gpMaker.add(1,"set size ratio 2");
  gpMaker.add(1,"set xrange[0:-80]");
  gpMaker.add(1,"set yrange[-80:80]");
  gpMaker.add(1,"INIT_RX = 0.0");
  gpMaker.add(1,"INIT_RY =-39.00");

  // gpMaker.add(1,"PMAX_X  = 58.0");
  // gpMaker.add(1,"PMIN_X  =-40.0");
  // gpMaker.add(1,"PMAX_Y  = 31.5");
  // gpMaker.add(1,"PMIN_Y  =-31.5");
  gpMaker.add(1,"PMAX_X  = "+to_string(x_length_top));
  gpMaker.add(1,"PMIN_X  = "+to_string(x_length_bottom));
  gpMaker.add(1,"PMAX_Y  = "+to_string(y_length));
  gpMaker.add(1,"PMIN_Y  =-"+to_string(y_length));

  gpMaker.add(1,"set arrow 1 from INIT_RY+PMIN_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMIN_X nohead lw 1");
  gpMaker.add(1,"set arrow 2 from INIT_RY+PMAX_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMAX_X nohead lw 1");
  gpMaker.add(1,"set arrow 3 from INIT_RY+PMAX_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMAX_X nohead lw 2");
  gpMaker.add(1,"set arrow 4 from INIT_RY+PMIN_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMIN_X nohead lw 2");

  gpMaker.add(2,"YLABEL_OFFSET_X = -0.9");
  gpMaker.add(2,"set xtics 40");
  gpMaker.add(2,"set parametric");
  gpMaker.add(2,"set size ratio 2");
  gpMaker.add(2,"set xrange[80:0]");
  gpMaker.add(2,"set yrange[-80:80]");
  gpMaker.add(2,"INIT_LX = 0.0");
  gpMaker.add(2,"INIT_LY = 39.00");

  // gpMaker.add(2,"PMAX_X  = 58.0");
  // gpMaker.add(2,"PMIN_X  =-40.0");
  // gpMaker.add(2,"PMAX_Y  = 31.5");
  // gpMaker.add(2,"PMIN_Y  =-31.5");
  gpMaker.add(2,"PMAX_X  = "+to_string(x_length_top));
  gpMaker.add(2,"PMIN_X  = "+to_string(x_length_bottom));
  gpMaker.add(2,"PMAX_Y  = "+to_string(y_length));
  gpMaker.add(2,"PMIN_Y  =-"+to_string(y_length));

  gpMaker.add(2,"set arrow 1 from INIT_LY+PMIN_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMIN_X nohead lw 2");
  gpMaker.add(2,"set arrow 2 from INIT_LY+PMAX_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMAX_X nohead lw 2");
  gpMaker.add(2,"set arrow 3 from INIT_LY+PMAX_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMAX_X nohead lw 1");
  gpMaker.add(2,"set arrow 4 from INIT_LY+PMIN_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMIN_X nohead lw 1");
  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage(info.value.joint);

  texMaker.setTexName("localCoP");
  texMaker.setCaption("Local CoP values.");
  texMaker.makeTex();
}
