/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::vrpDes4walking(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  // double y_length = 31.5;
  // double x_length_top = 58;
  // double x_length_bottom = -40;
  double y_length = 21;
  double x_length_top = 116/3;
  double x_length_bottom = -80/3;

  reset();
  setFileName("vrpDesx");
  makeDat("t-vrpDesx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Desired VRP x [mm]");
  gpMaker.setUnit("m");

  gpMaker.add("set ytics 60");
  gpMaker.add("set yrange[-30:120]");

  int ob = 1;
  int step = 10;
  // *********************************
  gpMaker.add("set object "+to_string(ob)+" rect from 0, "+to_string(x_length_bottom)+" to 0.6, "+to_string(x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 0.9, "+to_string(x_length_bottom)+" to 1.1, "+to_string(x_length_top+step)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 1.4, "+to_string(x_length_bottom+step)+" to 1.6, "+to_string(x_length_top+2*step)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 1.9, "+to_string(x_length_bottom+2*step)+" to 2.1, "+to_string(x_length_top+3*step)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.4, "+to_string(x_length_bottom+3*step)+" to 2.6, "+to_string(x_length_top+4*step)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.9, "+to_string(x_length_bottom+4*step)+" to 3.1, "+to_string(x_length_top+5*step)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.4, "+to_string(x_length_bottom+5*step)+" to 3.6, "+to_string(x_length_top+6*step)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.9, "+to_string(x_length_bottom+6*step)+" to 4.1, "+to_string(x_length_top+7*step)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 4.4, "+to_string(x_length_bottom+7*step)+" to 1e+3, "+to_string(x_length_top+7*step)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add("set object "+to_string(ob)+" rect from 0.6, "+to_string(x_length_bottom)+" to 0.9, "+to_string(x_length_top)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 1.1, "+to_string(x_length_bottom+step)+" to 1.4, "+to_string(x_length_top+step)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 1.6, "+to_string(x_length_bottom+2*step)+" to 1.9, "+to_string(x_length_top+2*step)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.1, "+to_string(x_length_bottom+3*step)+" to 2.4, "+to_string(x_length_top+3*step)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.6, "+to_string(x_length_bottom+4*step)+" to 2.9, "+to_string(x_length_top+4*step)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.1, "+to_string(x_length_bottom+5*step)+" to 3.4, "+to_string(x_length_top+5*step)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.6, "+to_string(x_length_bottom+6*step)+" to 3.9, "+to_string(x_length_top+6*step)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 4.1, "+to_string(x_length_bottom+7*step)+" to 4.4, "+to_string(x_length_top+7*step)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // *********************************

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("vrpDesy");
  makeDat("t-vrpDesy");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Desired VRP y [mm]");
  gpMaker.setUnit("m");

  gpMaker.add("set yrange[-70:70]");

  ob = 1;
  gpMaker.add("set object "+to_string(ob)+" rect from 0, (-39-"+to_string(y_length)+") to 0.6, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 0.9, (-39-"+to_string(y_length)+") to 1.1, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 1.4, (-39-"+to_string(y_length)+") to 1.6, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 1.9, (-39-"+to_string(y_length)+") to 2.1, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.4, (-39-"+to_string(y_length)+") to 2.6, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.9, (-39-"+to_string(y_length)+") to 3.1, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.4, (-39-"+to_string(y_length)+") to 3.6, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.9, (-39-"+to_string(y_length)+") to 4.1, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 4.4, (-39-"+to_string(y_length)+") to 1e+3, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add("set object "+to_string(ob)+" rect from 0.6, (-39-"+to_string(y_length)+") to 0.9, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 1.6, (-39-"+to_string(y_length)+") to 1.9, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.6, (-39-"+to_string(y_length)+") to 2.9, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.6, (-39-"+to_string(y_length)+") to 3.9, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  gpMaker.add("set object "+to_string(ob)+" rect from 1.1, (39-"+to_string(y_length)+") to 1.4, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 2.1, (39-"+to_string(y_length)+") to 2.4, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 3.1, (39-"+to_string(y_length)+") to 3.4, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  gpMaker.add("set object "+to_string(ob)+" rect from 4.1, (39-"+to_string(y_length)+") to 4.4, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  // static
  // *********************************
  // gpMaker.add("set object "+to_string(ob)+" rect from 0, (-39-"+to_string(y_length)+") to 1.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 1.75, (-39-"+to_string(y_length)+") to 2.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 2.75, (-39-"+to_string(y_length)+") to 3.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 3.75, (-39-"+to_string(y_length)+") to 4.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 4.75, (-39-"+to_string(y_length)+") to 5.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 5.75, (-39-"+to_string(y_length)+") to 6.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 6.75, (-39-"+to_string(y_length)+") to 7.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 7.75, (-39-"+to_string(y_length)+") to 8.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 8.75, (-39-"+to_string(y_length)+") to 9.25, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 9.75, (-39-"+to_string(y_length)+") to 1e+3, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  // gpMaker.add("set object "+to_string(ob)+" rect from 1.25, (-39-"+to_string(y_length)+") to 1.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 3.25, (-39-"+to_string(y_length)+") to 3.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 5.25, (-39-"+to_string(y_length)+") to 5.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 7.25, (-39-"+to_string(y_length)+") to 7.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 9.25, (-39-"+to_string(y_length)+") to 9.75, (-39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  // gpMaker.add("set object "+to_string(ob)+" rect from 2.25, (39-"+to_string(y_length)+") to 2.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 4.25, (39-"+to_string(y_length)+") to 4.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 6.25, (39-"+to_string(y_length)+") to 6.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // gpMaker.add("set object "+to_string(ob)+" rect from 8.25, (39-"+to_string(y_length)+") to 8.75, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
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

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("vrpDes");
  texMaker.setCaption("Desired VRP values.");
  texMaker.makeTex();
}
