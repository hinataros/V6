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

  gpMaker.add("set ytics 300");
  gpMaker.add("set yrange[-30:610]");

  int ob = 1;

  int step = 80;

  double dtstep = 0.5;
  double dtDSstep = 0.1;
  double dtDSini = 0.05;

  double tinit = 0.;
  double tend = 0.;
  double pinit = 0.;
  double pend = 0.;

  // *********************************
  // double support
  // *********************************
  // tinit = 0.; tend = dtstep + dtDSini;
  tinit = 0.; tend = dtstep/2 + dtDSini;
  pinit = x_length_bottom; pend = x_length_top;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder"); ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  pinit += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tend)+", "+to_string(pinit)+" to 1e+3, "+to_string(pend)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  // single support
  // *********************************
  // tinit = dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  tinit = dtstep/2+dtDSini; tend = tinit+(dtstep-dtDSstep);
  pinit = x_length_bottom; pend = x_length_top;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep; tend = tinit+(dtstep-dtDSstep);
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep; tend = tinit+(dtstep-dtDSstep);
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep; tend = tinit+(dtstep-dtDSstep);
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep; tend = tinit+(dtstep-dtDSstep);
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep; tend = tinit+(dtstep-dtDSstep);
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep; tend = tinit+(dtstep-dtDSstep);
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep; tend = tinit+(dtstep-dtDSstep);
  pinit += step; pend += step;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", "+to_string(pinit)+" to "+to_string(tend)+", "+to_string(pend)+" behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // *********************************
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

    string norm = to_string(y_length);
  // double support
  // *********************************
  // tinit = 0.; tend = dtstep+dtDSini;
  tinit = 0.; tend = dtstep/2+dtDSini;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  tinit = tend+(dtstep-dtDSstep); tend = tinit+dtDSstep;
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;

  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tend)+", (-39-"+norm+") to 1e+3, (39+"+norm+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");ob++;


  // right leg support
  // *********************************
  // tinit = dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  tinit = dtstep/2+dtDSini; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (-39+"+norm+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (-39+"+norm+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (-39+"+norm+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (-39-"+norm+") to "+to_string(tend)+", (-39+"+norm+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;


  // left leg support
  // *********************************
  // tinit = 2*dtstep+dtDSini; tend = tinit+(dtstep-dtDSstep);
  tinit = dtstep+dtstep/2+dtDSini; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;

  tinit = tend+dtDSstep+dtstep; tend = tinit+(dtstep-dtDSstep);
  gpMaker.add("set object "+to_string(ob)+" rect from "+to_string(tinit)+", (39-"+norm+") to "+to_string(tend)+", (39+"+norm+") behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder");ob++;
  // *********************************
  // *********************************

  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("vrpDes");
  texMaker.setCaption("Desired VRP values.");
  texMaker.makeTex();
}
