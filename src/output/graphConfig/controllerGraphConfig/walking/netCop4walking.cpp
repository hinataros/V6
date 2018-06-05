/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::netCop4walking(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
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
  setFileName("netCoPx");
  makeDat("t-rpx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("net CoP x [mm]");
  gpMaker.setUnit("m");
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

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("netCoPy");
  makeDat("t-rpy");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("net CoP y [mm]");
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

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("netCoP");
  texMaker.setCaption("net CoP values.");
  texMaker.makeTex();
}
