/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::stabilityIndex(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  // double y_length = 31.5;
  // double x_length_top = 58;
  // double x_length_bottom = -40;
  double y_length = 21;
  double x_length_top = 116/3;
  double x_length_bottom = -80/3;

  reset();
  setFileName("xStabilityIndex");
  makeDat("t-xStabilityIndex");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Stability index x [mm]");
  gpMaker.setUnit("m");
  gpMaker.add("set yrange[-80:80]");

  double x_offset_top = 0.;
  double x_offset_bottom = 0.;
  // double x_offset_top = 40.;
  // double x_offset_bottom = -40.;

  gpMaker.add("set object 1 rect from 0, ("+to_string(x_offset_bottom+x_length_bottom)+") to 1e+3, "+to_string(x_offset_top+x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

  // // zeff
  // gpMaker.add("set object 1 rect from 0, ("+to_string(x_offset_bottom)+") to 1e+3, "+to_string(x_offset_top+x_length_top)+" behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

  gpMaker.setDimention(4);
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

  gpMaker.add("set yrange[-70:70]");
  gpMaker.add("set object 1 rect from 0, ("+to_string(y_length)+") to 1e+3, (39+"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  // zeff
  // gpMaker.add("set object 1 rect from 0, (39-0.5) to 1e+3, (39+0.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");
  gpMaker.add("set object 2 rect from 0, (-"+to_string(y_length)+") to 1e+3, (-39-"+to_string(y_length)+") behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder");

  gpMaker.setDimention(4);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("stabilityIndex");
  makeDat("xStabilityIndex-yStabilityIndex");

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

  double ankle_offset_x = 6.;
  double ankle_size = 3.;

  double foot_size_x = 64.;
  double foot_size_y = 42.;

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

  gpMaker.setDimention(4);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("stabilityIndex");
  texMaker.setCaption("net CoP and gCoM and xCoM values.");
  texMaker.makeTex();
}
