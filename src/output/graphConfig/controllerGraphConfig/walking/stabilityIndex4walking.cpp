/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::stabilityIndex4walking(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  double y_length = 31.5;
  double x_length_top = 58;
  double x_length_bottom = -40;
  // double y_length = 21;
  // double x_length_top = 116/3;
  // double x_length_bottom = -80/3;

  reset();
  setFileName("xStabilityIndex");
  makeDat("t-xStabilityIndex");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Stability index x [mm]");
  gpMaker.setUnit("m");

  gpMaker.add("set ytics 60");
  gpMaker.add("set yrange[-60:480]");

  // *********************************
  double t0 = 1.25;
  double tf = 1.75;

  int rrf = 0;
  int rlf = 0;

  int step = 18;
  gpMaker.add("set object 1 rect from 0, "+to_string(x_length_bottom)+" to 1.25, "+to_string(x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  for(int i=2; i<step; i+=2){
    gpMaker.add("set object "+to_string(i)+" rect from "+to_string(t0)+", "+to_string(x_length_bottom)+"+"+to_string(rlf)+" to "+to_string(tf)+", "+to_string(x_length_top)+"+"+to_string(rrf)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");
    gpMaker.add("set object "+to_string(i+1)+" rect from "+to_string(t0+0.5)+", "+to_string(x_length_bottom)+"+"+to_string(rlf)+" to "+to_string(tf+0.5)+", "+to_string(x_length_top)+"+"+to_string(rrf+50)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

    t0 += 1.;
    tf += 1.;

    rrf += 50;
    rlf += 50;
  }

  gpMaker.add("set object 100 rect from "+to_string(t0)+", "+to_string(x_length_bottom)+"+"+to_string(rlf)+" to "+to_string(tf)+", "+to_string(x_length_top)+"+"+to_string(rrf)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");
  gpMaker.add("set object 101 rect from "+to_string(t0+0.5)+", "+to_string(x_length_bottom)+"+"+to_string(rlf)+" to 1e+3, "+to_string(x_length_top)+"+"+to_string(rrf)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  // *********************************

  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("yStabilityIndex");
  makeDat("t-yStabilityIndex");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Stability index y [mm]");
  gpMaker.setUnit("m");

  gpMaker.add("set yrange[-80:80]");

  // *********************************
  int ob = 1;
  gpMaker.add("set object "+to_string(ob)+" rect from 0, (-39-"+to_string(y_length)+") to 1.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 1.75, (-39-"+to_string(y_length)+") to 2.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.75, (-39-"+to_string(y_length)+") to 3.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.75, (-39-"+to_string(y_length)+") to 4.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 4.75, (-39-"+to_string(y_length)+") to 5.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 5.75, (-39-"+to_string(y_length)+") to 6.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 6.75, (-39-"+to_string(y_length)+") to 7.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 7.75, (-39-"+to_string(y_length)+") to 8.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 8.75, (-39-"+to_string(y_length)+") to 9.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 9.75, (-39-"+to_string(y_length)+") to 1e+3, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add("set object "+to_string(ob)+" rect from 1.25, (-39-"+to_string(y_length)+") to 1.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.25, (-39-"+to_string(y_length)+") to 3.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 5.25, (-39-"+to_string(y_length)+") to 5.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 7.25, (-39-"+to_string(y_length)+") to 7.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 9.25, (-39-"+to_string(y_length)+") to 9.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  gpMaker.add("set object "+to_string(ob)+" rect from 2.25, (39-"+to_string(y_length)+") to 2.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 4.25, (39-"+to_string(y_length)+") to 4.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 6.25, (39-"+to_string(y_length)+") to 6.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 8.25, (39-"+to_string(y_length)+") to 8.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // *********************************

  // gpMaker.add("set object "+to_string(ob)+" rect from 0, (-39+31.5) to 1.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 1.75, (-39+31.5) to 2.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 2.75, (-39+31.5) to 3.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 3.75, (-39+31.5) to 4.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 4.75, (-39+31.5) to 5.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 5.75, (-39+31.5) to 6.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 6.75, (-39+31.5) to 7.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 7.75, (-39+31.5) to 8.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 8.75, (-39+31.5) to 9.25, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 9.75, (-39+31.5) to 1e+3, (39-31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 0, (-39+31.5) to 1.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 1.75, (-39+31.5) to 2.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 2.75, (-39+31.5) to 3.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 3.75, (-39+31.5) to 4.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 4.75, (-39+31.5) to 5.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 5.75, (-39+31.5) to 6.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 6.75, (-39+31.5) to 7.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 7.75, (-39+31.5) to 8.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 8.75, (-39+31.5) to 9.25, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 9.75, (-39+31.5) to 1e+3, (39-31.5) behind lw 0 fc rgb 'royalblue' fill solid 0.2 noborder");ob++;

  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("stabilityIndex");
  makeDat("yStabilityIndex-xStabilityIndex");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setXLabel("x [mm]");
  gpMaker.setYLabel("y [mm]");
  gpMaker.setUnit("m");
  gpMaker.add("YLABEL_OFFSET_X = -0.9");
  gpMaker.add("set xtics 160");
  // gpMaker.add("set ytics 40");
  gpMaker.add("set size ratio 2");
  gpMaker.add("set xrange[160:-160]");
  gpMaker.add("set yrange[-80:480]");
  gpMaker.add("INIT_RX = 0.0");
  gpMaker.add("INIT_RY =-39.00");
  gpMaker.add("INIT_LX = 0.0");
  gpMaker.add("INIT_LY = 39.00");

  // gpMaker.add("PMAX_X  = 58.0");
  // gpMaker.add("PMIN_X  =-40.0");
  // gpMaker.add("PMAX_Y  = 31.5");
  // gpMaker.add("PMIN_Y  =-31.5");
  gpMaker.add("PMAX_X  = "+to_string(x_length_top));
  gpMaker.add("PMIN_X  = "+to_string(x_length_bottom));
  gpMaker.add("PMAX_Y  = "+to_string(y_length));
  gpMaker.add("PMIN_Y  =-"+to_string(y_length));

  gpMaker.add("set arrow 1 from INIT_RY+PMIN_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMIN_X nohead lw 1");
  gpMaker.add("set arrow 2 from INIT_RY+PMAX_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMAX_X nohead lw 1");
  gpMaker.add("set arrow 3 from INIT_RY+PMAX_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMAX_X nohead lw 2");
  gpMaker.add("set arrow 4 from INIT_RY+PMIN_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMIN_X nohead lw 2");
  gpMaker.add("set arrow 5 from INIT_LY+PMIN_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMIN_X nohead lw 2");
  gpMaker.add("set arrow 6 from INIT_LY+PMAX_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMAX_X nohead lw 2");
  gpMaker.add("set arrow 7 from INIT_LY+PMAX_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMAX_X nohead lw 1");
  gpMaker.add("set arrow 8 from INIT_LY+PMIN_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMIN_X nohead lw 1");
  gpMaker.add("set arrow 9  from INIT_LY+PMAX_Y, INIT_LX+PMAX_X to INIT_RY+PMAX_Y, INIT_RX+PMAX_X nohead lw 2");
  gpMaker.add("set arrow 10 from INIT_LY+PMIN_Y, INIT_LX+PMIN_X to INIT_RY+PMIN_Y, INIT_RX+PMIN_X nohead lw 2");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("stabilityIndex");
  texMaker.setCaption("net CoP and gCoM and xCoM values.");
  texMaker.makeTex();
}
