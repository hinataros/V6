/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::netCop(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("netCoPx");
  makeDat("t-rpx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("net CoP x [mm]");
  gpMaker.setUnit("m");
  gpMaker.add("set yrange[-60:80]");
  gpMaker.add("set object 1 rect from 0, -40 to 1e+3, 58 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
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
  gpMaker.add("set object 1 rect from 0, (39-31.5) to 1e+3, (39+31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.add("set object 2 rect from 0, (-39-31.5) to 1e+3, (-39+31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.setDimention(1);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("netCoP");
  texMaker.setCaption("net CoP values.");
  texMaker.makeTex();
}
