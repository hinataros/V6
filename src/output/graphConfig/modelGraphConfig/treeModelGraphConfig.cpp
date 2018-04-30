/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::treeModelGraphConfig(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  // initialize
  // ************************************************
  nameNum = 1;
  setDatPath(config.dir.dat.ind+"model/");
  setDataNum(info.sim.n);
  setST(config.graph.st);

  GpMaker gpMaker("model");

  gpMaker.setMainGpName("model");
  gpMaker.setGpPath(config.dir.gp.ind);

  TexMaker texMaker("model");
  texMaker.setMainTexName(config.result.name.ind);
  texMaker.setResultPath(config.dir.result);
  texMaker.setEpsPath(config.dir.eps.ind);
  texMaker.setPdfPath(config.dir.pdf.ind);
  // ************************************************

  // config
  // ************************************************
  baseTrans(config, info, gpMaker, texMaker);
  baseRot(config, info, gpMaker, texMaker);
  joint(config, info, gpMaker, texMaker);
  eeTrans(config, info, gpMaker, texMaker);
  eeRot(config, info, gpMaker, texMaker);
  eeWrench(config, info, gpMaker, texMaker);
  com(config, info, gpMaker, texMaker);
  spatialMom(config, info, gpMaker, texMaker);
  // ************************************************

  // main
  gpMaker.makeMainGp();
  texMaker.makeMainTex();
}
