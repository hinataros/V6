/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::netCop(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("netCoPx");

  setTimeDependentDat("rpx");
  makeDat();

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

  setTimeDependentDat("rpy");
  makeDat();

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

  reset();
  setFileName("netCoP");

  setDatNum(2);
  setDatName(1, "rpw2k");
  setDatName(2, "rp");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setXLabel("x [mm]");
  gpMaker.setYLabel("y [mm]");
  gpMaker.setUnit("m");

  gpMaker.redef("YLABEL_OFFSET_X = -0.45");
  gpMaker.add("set xtics 40");
  gpMaker.add("set parametric");
  gpMaker.add("set size square");
  gpMaker.add("set xrange[-80:80]");
  gpMaker.add("set yrange[-80:80]");

  double ankle_offset_x = 9.;
  double ankle_size = 3.;

  double foot_size_x = 98.;
  double foot_size_y = 63.;

  double foot_pos_rx = 0.;
  double foot_pos_ry = -39.;
  double foot_pos_lx = 0.;
  double foot_pos_ly = 39.;

  int ob = 1;

  // right foot print
  gpMaker.add("set object "+to_string(ob)+" circle at first "+to_string(foot_pos_rx)+", "+to_string(foot_pos_ry)+" size "+to_string(ankle_size)+" fs empty border rgb 'black'"); ob++;

  foot_pos_rx = ankle_offset_x;
  gpMaker.add("set object "+to_string(ob)+" rect at first "+to_string(foot_pos_rx)+", "+to_string(foot_pos_ry)+" size "+to_string(foot_size_x)+", "+to_string(foot_size_y)+" fs empty border rgb 'black'"); ob++;

  // left foot print
  gpMaker.add("set object "+to_string(ob)+" circle at first "+to_string(foot_pos_lx)+", "+to_string(foot_pos_ly)+" size "+to_string(ankle_size)+" fs empty border rgb 'black'"); ob++;

  foot_pos_lx = ankle_offset_x;
  gpMaker.add("set object "+to_string(ob)+" rect at first "+to_string(foot_pos_lx)+", "+to_string(foot_pos_ly)+" size "+to_string(foot_size_x)+", "+to_string(foot_size_y)+" fs empty border rgb 'black'"); ob++;

  gpMaker.setDimention(6);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("netCoP");
  texMaker.setCaption("net CoP values.");
  texMaker.makeTex();
}
