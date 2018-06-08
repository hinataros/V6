/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::footPrint(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("footPrint");
  makeDat("rXDesy-rXDesx");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setXLabel("Desired DCM y [mm]");
  gpMaker.setYLabel("Desired DCM x [mm]");
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
  gpMaker.add("PMAX_X  = 58.0");
  gpMaker.add("PMIN_X  =-40.0");
  gpMaker.add("PMAX_Y  = 31.5");
  gpMaker.add("PMIN_Y  =-31.5");
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

  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("footPrint");
  texMaker.setCaption("Foot print.");
  texMaker.makeTex();
}
