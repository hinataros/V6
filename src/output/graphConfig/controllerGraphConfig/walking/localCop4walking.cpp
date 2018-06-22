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
  texMaker.setLimbNum(3, false);
  texMaker.setLimbNum(4, false);

  // double y_length = 31.5;
  // double x_length_top = 58;
  // double x_length_bottom = -40;
  double y_length = 21;
  double x_length_top = 116/3;
  double x_length_bottom = -80/3;

  reset();
  setFileName("localCoPx");
  makeDat("t-rpkx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  gpMaker.setLimbNum(3, false);
  gpMaker.setLimbNum(4, false);
  gpMaker.setYLabel("EE CoP x [mm]");
  gpMaker.setUnit("m");
  gpMaker.add(1,"set yrange[-30:40]");

  int ob = 1;

  double dtstep = 0.8;
  double dtDSstep = 0.3;
  double dtDSini = 0.15;

  double tinit = 0.;
  double tend = 0.;
  string bottom = "";
  string top = "";

  // double support
  // *********************************
  bottom = to_string(x_length_bottom);
  top = to_string(x_length_top);

  tinit = 0.; tend = dtstep + dtDSini;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  // single support
  // *********************************
  tinit = dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;
  // *********************************

  ob=1;
  gpMaker.add(2,"set yrange[-30:40]");
  // *********************************

  // double support
  // *********************************
  tinit = 0.; tend = dtstep + dtDSini;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  // single support
  // *********************************
  tinit = 2*dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  // *********************************

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
  gpMaker.setLimbNum(3, false);
  gpMaker.setLimbNum(4, false);
  gpMaker.setYLabel("EE CoP y [mm]");
  gpMaker.setUnit("m");
  gpMaker.add(1,"set yrange[-30:30]");

  ob = 1;

  // double support
  // *********************************
  bottom = "-"+to_string(y_length);
  top = to_string(y_length);

  tinit = 0.; tend = dtstep + dtDSini;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  // single support
  // *********************************
  tinit = dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(1,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;
  // *********************************

  ob=1;
  gpMaker.add(2,"set yrange[-30:30]");
  // *********************************

  // double support
  // *********************************
  tinit = 0.; tend = dtstep + dtDSini;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  // single support
  // *********************************
  tinit = 2*dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add(2,"set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+bottom+" to "+to_string(tend)+", "+top+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder"); ob++;

  // *********************************

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
