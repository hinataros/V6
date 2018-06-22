/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::footPrint(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  // double y_length = 31.5;
  // double x_length_top = 58;
  // double x_length_bottom = -40;
  double y_length = 21;
  double x_length_top = 116/3;
  double x_length_bottom = -80/3;

  texMaker.reset();

  reset();
  setFileName("footPrint");
  makeDat("foot print");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setXLabel("y [mm]");
  gpMaker.setYLabel("x [mm]");
  gpMaker.setUnit("m");

  gpMaker.add("set xtics 40");
  gpMaker.add("set parametric");
  gpMaker.add("set size square");
  gpMaker.add("set xrange[80:-80]");
  gpMaker.add("set yrange[-80:80]");
  gpMaker.add("INIT_RX = 0.0");
  gpMaker.add("INIT_RY =-39.00");
  gpMaker.add("INIT_LX = 0.0");
  gpMaker.add("INIT_LY = 39.00");
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

  gpMaker.add("set style arrow 1 nohead dt 2");
  gpMaker.add("set arrow 11 from INIT_RY, INIT_RX+PMIN_X to INIT_RY, INIT_RX+PMAX_X as 1");
  gpMaker.add("set arrow 12 from INIT_LY, INIT_LX+PMIN_X to INIT_LY, INIT_LX+PMAX_X as 1");

  gpMaker.setDimention(2);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("footPrint");
  texMaker.setCaption("Foot print.");
  texMaker.makeTex();
}
