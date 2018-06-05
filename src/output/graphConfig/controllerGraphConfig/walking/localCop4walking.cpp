/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::localCop4walking(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.value.joint);

  double y_length = 31.5;
  double x_length_top = 58;
  double x_length_bottom = -40;
  // double y_length = 21;
  // double x_length_top = 116/3;
  // double x_length_bottom = -80/3;

  reset();
  setFileName("localCoPx");
  makeDat("t-rpkx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE CoP x [mm]");
  gpMaker.setUnit("m");
  // walking
  int ob = 1;
  gpMaker.add(1,"set yrange[-60:480]");
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 0, -40 to 2.25, 58 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 2.75, -40+100 to 4.25, 58+100 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 4.75, -40+100+100 to 6.25, 58+100+100 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 6.75, -40+100+100+100 to 8.25, 58+100+100+100 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 8.75, -40+100+100+100+100 to 1e+3, 58+100+100+100+100 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add(1,"set object "+to_string(ob)+" rect from 1.25, -40 to 1.75, 58 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 3.25, -40+100 to 3.75, 58+100 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 5.25, -40+100+100 to 5.75, 58+100+100 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 7.25, -40+100+100+100 to 7.75, 58+100+100+100 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 9.25, -40+100+100+100+100 to 9.75, 58+100+100+100+100 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  ob=1;
  gpMaker.add(2,"set yrange[-60:480]");
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 0, -40 to 1.25, 58 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 1.75, -40+50 to 3.25, 58+50 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 3.75, -40+50+100 to 5.25, 58+50+100 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 5.75, -40+50+100+100 to 7.25, 58+50+100+100 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 7.75, -40+50+100+100+100 to 9.25, 58+50+100+100+100 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 9.75, -40+50+100+100+100+50 to 1e+3, 58+50+100+100+100+50 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add(2,"set object "+to_string(ob)+" rect from 2.25, -40+50 to 2.75, 58+50 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 4.25, -40+50+100 to 4.75, 58+50+100 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 6.25, -40+50+100+100 to 6.75, 58+50+100+100 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 8.25, -40+50+100+100+100 to 8.75, 58+50+100+100+100 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  // gpMaker.add(1,"set object 1 rect from 0, -40 to 1e+3, 58 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  // gpMaker.add(1,"set object 3 rect from 2.25, -40 to 2.75, 58 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");
  // gpMaker.add(2,"set yrange[-60:80]");
  // gpMaker.add(2,"set object 1 rect from 0, -40 to 1e+3, 58 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  // gpMaker.add(2,"set object 2 rect from 1.25, -40 to 1.75, 58 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");
  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("localCoPy");
  makeDat("t-rpky");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setYLabel("EE CoP y [mm]");
  gpMaker.setUnit("m");

  // walking
  gpMaker.add(1,"set yrange[-80:0]");
  ob=1;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 0, (-39-"+to_string(y_length)+") to 2.25, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 2.75, (-39-"+to_string(y_length)+") to 4.25, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 4.75, (-39-"+to_string(y_length)+") to 6.25, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 6.75, (-39-"+to_string(y_length)+") to 8.25, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 8.75, (-39-"+to_string(y_length)+") to 1e+3, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add(1,"set object "+to_string(ob)+" rect from 1.25, (-39-"+to_string(y_length)+") to 1.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 3.25, (-39-"+to_string(y_length)+") to 3.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 5.25, (-39-"+to_string(y_length)+") to 5.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 7.25, (-39-"+to_string(y_length)+") to 7.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from 9.25, (-39-"+to_string(y_length)+") to 9.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  gpMaker.add(2,"set yrange[0:80]");
  ob=1;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 0, (39-"+to_string(y_length)+") to 1.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 1.75, (39-"+to_string(y_length)+") to 3.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 3.75, (39-"+to_string(y_length)+") to 5.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 5.75, (39-"+to_string(y_length)+") to 7.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 7.75, (39-"+to_string(y_length)+") to 9.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 9.75, (39-"+to_string(y_length)+") to 1e+3, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add(2,"set object "+to_string(ob)+" rect from 2.25, (39-"+to_string(y_length)+") to 2.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 4.25, (39-"+to_string(y_length)+") to 4.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 6.25, (39-"+to_string(y_length)+") to 6.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from 8.25, (39-"+to_string(y_length)+") to 8.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  // // gpMaker.add(1,"set object 1 rect from 0, (-39-31.5) to 1e+3, (-39+31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  // // gpMaker.add(1,"set object 2 rect from 1.25, (-39-31.5) to 1.75, (-39+31.5) behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");
  // gpMaker.add(1,"set object 3 rect from 2.25, (-39-31.5) to 2.75, (-39+31.5) behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");
  // gpMaker.add(2,"set object 1 rect from 0, (39-31.5) to 1e+3, (39+31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  // gpMaker.add(2,"set object 2 rect from 1.25, (39-31.5) to 1.75, (39+31.5) behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");
  // // gpMaker.add(2,"set object 3 rect from 2.25, (39-31.5) to 2.75, (39+31.5) behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");
  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  // reset();
  // setFileName("localCoPx-y");
  // makeDat("rpky-rpkx");

  // gpMaker.reset();
  // gpMaker.setName(file_name);
  // gpMaker.setLimb(info.value.joint);
  // gpMaker.setXLabel("EE local CoP y [mm]");
  // gpMaker.setYLabel("EE local CoP x [mm]");
  // gpMaker.chUnit("m");

  // gpMaker.redef(1,"YLABEL_OFFSET_X = -0.9");
  // gpMaker.add(1,"set xtics 40");
  // gpMaker.add(1,"set parametric");
  // gpMaker.add(1,"set size ratio 2");
  // gpMaker.add(1,"set xrange[0:-80]");
  // gpMaker.add(1,"set yrange[-80:80]");
  // gpMaker.add(1,"INIT_RX = 0.0");
  // gpMaker.add(1,"INIT_RY =-39.00");
  // gpMaker.add(1,"PMAX_X  = 58.0");
  // gpMaker.add(1,"PMIN_X  =-40.0");
  // gpMaker.add(1,"PMAX_Y  = 31.5");
  // gpMaker.add(1,"PMIN_Y  =-31.5");
  // gpMaker.add(1,"set arrow 1 from INIT_RY+PMIN_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMIN_X nohead lw 1");
  // gpMaker.add(1,"set arrow 2 from INIT_RY+PMAX_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMAX_X nohead lw 1");
  // gpMaker.add(1,"set arrow 3 from INIT_RY+PMAX_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMAX_X nohead lw 2");
  // gpMaker.add(1,"set arrow 4 from INIT_RY+PMIN_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMIN_X nohead lw 2");

  // gpMaker.redef(2,"YLABEL_OFFSET_X = -0.9");
  // gpMaker.add(2,"set xtics 40");
  // gpMaker.add(2,"set parametric");
  // gpMaker.add(2,"set size ratio 2");
  // gpMaker.add(2,"set xrange[80:0]");
  // gpMaker.add(2,"set yrange[-80:80]");
  // gpMaker.add(2,"INIT_LX = 0.0");
  // gpMaker.add(2,"INIT_LY = 39.00");
  // gpMaker.add(2,"PMAX_X  = 58.0");
  // gpMaker.add(2,"PMIN_X  =-40.0");
  // gpMaker.add(2,"PMAX_Y  = 31.5");
  // gpMaker.add(2,"PMIN_Y  =-31.5");
  // gpMaker.add(2,"set arrow 1 from INIT_LY+PMIN_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMIN_X nohead lw 2");
  // gpMaker.add(2,"set arrow 2 from INIT_LY+PMAX_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMAX_X nohead lw 2");
  // gpMaker.add(2,"set arrow 3 from INIT_LY+PMAX_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMAX_X nohead lw 1");
  // gpMaker.add(2,"set arrow 4 from INIT_LY+PMIN_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMIN_X nohead lw 1");
  // gpMaker.setDimention(1);
  // gpMaker.makeGp();

  // texMaker.setName(file_name);
  // texMaker.addMinipage();

  texMaker.setTexName("localCoP");
  texMaker.setCaption("Local CoP values.");
  texMaker.makeTex();
}
