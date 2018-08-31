/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::accelerationGraphConfig(const Config &config, const TreeModel::Info &info)
{
  // initialize
  // ************************************************
  nameNum = 1;
  setDatPath(config.dir.dat.ind);
  setDataNum(config.clock.n);
  setST(config.gp.st);

  GpMaker gpMaker;

  gpMaker.setMainGpName();
  gpMaker.setGpPath(config.dir.gp.ind);

  TexMaker texMaker;
  texMaker.setMainTexName(config.result.name.ind);
  texMaker.setResultPath(config.dir.result);
  texMaker.setEpsPath(config.dir.eps.ind);
  texMaker.setPdfPath(config.dir.pdf.ind);
  // ************************************************

  // model config
  // ************************************************
  mix(config, info, gpMaker, texMaker);
  joint(config, info, gpMaker, texMaker);
  eeTrans(config, info, gpMaker, texMaker);
  eeRot(config, info, gpMaker, texMaker);
  eeWrench(config, info, gpMaker, texMaker);
  spatialMom(config, info, gpMaker, texMaker);
  // ************************************************

  // main
  gpMaker.makeMainGp();
  texMaker.makeMainTex();
}
