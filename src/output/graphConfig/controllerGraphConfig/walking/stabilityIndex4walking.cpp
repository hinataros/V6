/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::stabilityIndex4walking(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  // double y_length = 31.5;
  // double x_length_top = 58;
  // double x_length_bottom = -40;
  double scale = 1.;
  double y_length = 21*scale;
  double x_length_top = (116/3)*scale;
  double x_length_bottom = -(80/3)*scale;

  reset();
  setFileName("xStabilityIndex");

  setTimeDependentDat("xStabilityIndex");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Stability indicator x [mm]");
  gpMaker.setUnit("m");
  // gpMaker.setScale(-2);

  // // straight walk
  // gpMaker.add("set ytics 300");
  // gpMaker.add("set yrange[-30:750]");

  // updown walk
  // gpMaker.add("set ytics 300");
  gpMaker.add("set yrange[-30:300]");

  int ob = 1;

  // int step = 80;

  // double dtstep = 0.7;
  // double dtDSstep = 0.3;
  // double dtDSini = 0.06;

  // straight walk
  int num = 3;
  int step = 80*scale;

  double dtstep = 1.;
  double dtDSstep = 0.5;
  double dtDSini = 0.25;

  // // toe off straight walk
  // int num = 6;
  // int step = 80*scale;

  // double dtstep = 0.5;
  // double dtDSstep = 0.2;
  // double dtDSini = 0.1;

  // updown walk
  // int num = 14;
  // int step = 70*scale;

  // double dtstep = 0.8;
  // double dtDSstep = 0.2;
  // double dtDSini = 0.1;

  double tinit = 0.;
  double tend = 0.;
  double pinit = 0.;
  double pend = 0.;

  // double support
  // *********************************
  // tinit = 0.; tend = dtstep + dtDSini;
  tinit = 0.; tend = dtstep/2 + dtDSini;
  pinit = x_length_bottom; pend = x_length_top;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" back lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" back lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  for(int i=0; i<num; i++){
    tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
    pinit += step; pend += step;
    gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" back lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  }

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pinit += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" back lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tend)+", "+to_string(pinit)+" to 1e+3, "+to_string(pend)+" back lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  // single support
  // *********************************
  // tinit = dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  tinit = dtstep/2+dtDSini; tend = tinit+(dtstep-dtDSstep);
  pinit = x_length_bottom; pend = x_length_top;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" back lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  for(int i=0; i<num+1; i++){
    tinit = tend+dtDSstep; tend = tinit+(dtstep-dtDSstep);
    pinit += step; pend += step;
    gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" back lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  }
  // *********************************

  gpMaker.setDimention(4);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("yStabilityIndex");

  setTimeDependentDat("yStabilityIndex");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Stability indicator y [mm]");
  gpMaker.setUnit("m");

  gpMaker.add("set yrange[-70:70]");

  ob = 1;

  string norm = to_string(y_length);
  // double support
  // *********************************
  // tinit = 0.; tend = dtstep+dtDSini;
  tinit = 0.; tend = dtstep/2+dtDSini;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") back lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  for(int i=0; i<num+2; i++){
    tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
    gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") back lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  }

  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tend)+", (-39-"+norm+") to 1e+3, (39+"+norm+") back lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;


  // right leg support
  // *********************************
  // tinit = dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  tinit = dtstep/2+dtDSini; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (-39+"+norm+") back lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  for(int i=0; i<num/2; i++){
    tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
    gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (-39+"+norm+") back lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  }


  // left leg support
  // *********************************
  // tinit = 2*dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  tinit = dtstep+dtstep/2+dtDSini; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (39-"+norm+") to "+to_string(tend)+", (39+"+norm+") back lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  for(int i=0; i<num/2; i++){
    tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
    gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (39-"+norm+") to "+to_string(tend)+", (39+"+norm+") back lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  }
  // *********************************

  gpMaker.setDimention(4);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("stabilityIndex");

  setDatNum(4);
  setDatName(1, "gCoM");
  setDatName(2, "rndecmpDes");
  setDatName(3, "xCoM");
  setDatName(4, "eCMPRef");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setXLabel("x [mm]");
  gpMaker.setYLabel("y [mm]");
  gpMaker.setUnit("m");
  gpMaker.redef("XLABEL_OFFSET_Y = -0.4");
  gpMaker.redef("YLABEL_OFFSET_X = -0.25");
  gpMaker.add("set xtics 100");
  gpMaker.add("set ytics 60");
  gpMaker.add("set size ratio "+to_string(140./300));
  gpMaker.add("set xrange[-30:300]");
  gpMaker.add("set yrange[-70:70]");

  double ankle_offset_x = 6.;

  double foot_size_x = 64.;
  double foot_size_y = 42.;

  double foot_pos_rx = 0.;
  double foot_pos_ry = -39.;
  double foot_pos_lx = 0.;
  double foot_pos_ly = 39.;

  ob = 1;

  // right foot print
  foot_pos_rx = ankle_offset_x;
  gpMaker.add("set object "+to_string(ob)+" rect at first "+to_string(foot_pos_rx)+", "+to_string(foot_pos_ry)+" size "+to_string(foot_size_x)+", "+to_string(foot_size_y)+" fs empty border rgb 'black'"); ob++;

  for(int i=0; i<num/2; i++){
    foot_pos_rx += step*2;
    gpMaker.add("set object "+to_string(ob)+" rect at first "+to_string(foot_pos_rx)+", "+to_string(foot_pos_ry)+" size "+to_string(foot_size_x)+", "+to_string(foot_size_y)+" fs empty border rgb 'black'"); ob++;
  }

  foot_pos_rx += step;
  gpMaker.add("set object "+to_string(ob)+" rect at first "+to_string(foot_pos_rx)+", "+to_string(foot_pos_ry)+" size "+to_string(foot_size_x)+", "+to_string(foot_size_y)+" fs empty border rgb 'black'"); ob++;

  // left foot print
  foot_pos_lx = ankle_offset_x;
  gpMaker.add("set object "+to_string(ob)+" rect at first "+to_string(foot_pos_lx)+", "+to_string(foot_pos_ly)+" size "+to_string(foot_size_x)+", "+to_string(foot_size_y)+" fs empty border rgb 'black'"); ob++;

  foot_pos_lx += step;
  gpMaker.add("set object "+to_string(ob)+" rect at first "+to_string(foot_pos_lx)+", "+to_string(foot_pos_ly)+" size "+to_string(foot_size_x)+", "+to_string(foot_size_y)+" fs empty border rgb 'black'"); ob++;

  for(int i=0; i<num/2; i++){
    foot_pos_lx += step*2;
    gpMaker.add("set object "+to_string(ob)+" rect at first "+to_string(foot_pos_lx)+", "+to_string(foot_pos_ly)+" size "+to_string(foot_size_x)+", "+to_string(foot_size_y)+" fs empty border rgb 'black'"); ob++;
  }

  gpMaker.setDimention(4);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("stabilityIndex");
  texMaker.setCaption("net CoP and gCoM and xCoM values.");
  texMaker.makeTex();
}
