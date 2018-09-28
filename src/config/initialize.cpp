/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"

void RLS::Config::initialize()
{
  if(debug) DEBUG;

  conf = "default";

  result.name.cmp = "cmp";
  result.name.ind = "ind";
  flag.shm = false;

  model.name = "no model";

  controller.name = "no controller";

  gp.flag = false;
  gp.check = false;
  gp.st = 1.;
  gp.tstart = 0.;

  tex.flag = false;
  tex.title = "Simulation results";

  gif.flag = false;
  gif.st = 1.;
  gif.linkColor = "grey";
  gif.jointColor = "black";
  gif.terminal = true;
  gif.dir = true;

  gif.yz.flag = false;
  gif.yz.xMin = -0.5;
  gif.yz.xMax = 0.5;
  gif.yz.yMin = -0.5;
  gif.yz.yMax = 0.5;

  gif.xz.flag = false;
  gif.xz.xMin = -0.5;
  gif.xz.xMax = 0.5;
  gif.xz.yMin = -0.5;
  gif.xz.yMax = 0.5;

  gif.xy.flag = false;
  gif.xy.xMin = -0.5;
  gif.xy.xMax = 0.5;
  gif.xy.yMin = -0.5;
  gif.xy.yMax = 0.5;

  gif.all.flag = false;
  gif.all.xMin = -0.5;
  gif.all.xMax = 0.5;
  gif.all.yMin = -0.5;
  gif.all.yMax = 0.5;
  gif.all.zMin = -0.5;
  gif.all.zMax = 0.5;

  cho.st = 1.;
}
