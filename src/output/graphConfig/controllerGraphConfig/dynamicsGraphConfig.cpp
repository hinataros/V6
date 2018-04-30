/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::dynamicsGraphConfig(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  // initialize
  // ************************************************
  nameNum = 1;
  setDatPath(config.dir.dat.ind+"controller/");
  setDataNum(info.sim.n);
  setST(config.graph.st);

  GpMaker gpMaker("controller");

  gpMaker.setMainGpName("controller");
  gpMaker.setGpPath(config.dir.gp.ind);

  TexMaker texMaker("controller");
  texMaker.setMainTexName(config.result.name.ind);
  texMaker.setResultPath(config.dir.result);
  texMaker.setEpsPath(config.dir.eps.ind);
  texMaker.setPdfPath(config.dir.pdf.ind);
  // ************************************************

  // config
  // ************************************************
  baseTransDes(config, info, gpMaker, texMaker);
  baseRotDes(config, info, gpMaker, texMaker);
  dcmDes(config, info, gpMaker, texMaker);
  eeTransDes(config, info, gpMaker, texMaker);
  eeRotDes(config, info, gpMaker, texMaker);
  baseTransErr(config, info, gpMaker, texMaker);
  baseRotErr(config, info, gpMaker, texMaker);
  comErr(config, info, gpMaker, texMaker);
  dcmErr(config, info, gpMaker, texMaker);
  eeTransErr(config, info, gpMaker, texMaker);
  eeRotErr(config, info, gpMaker, texMaker);
  eeWrenchErr(config, info, gpMaker, texMaker);
  rcMomRef(config, info, gpMaker, texMaker);
  eeWrenchRef(config, info, gpMaker, texMaker);
  extWrenchRef(config, info, gpMaker, texMaker);
  jointTorque(config, info, gpMaker, texMaker);
  localCop(config, info, gpMaker, texMaker);
  netCop(config, info, gpMaker, texMaker);
  stabilityIndex(config, info, gpMaker, texMaker);
  // ************************************************

  // main
  gpMaker.makeMainGp();
  texMaker.makeMainTex();
}
