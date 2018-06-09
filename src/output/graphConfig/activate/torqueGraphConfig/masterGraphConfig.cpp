/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::masterGraphConfig(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  // initialize
  // ************************************************
  nameNum = 1;
  setDatPath(config.dir.dat.ind);
  setDataNum(info.sim.n);
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

  // des
  dcmDes(config, info, gpMaker, texMaker);
  baseRotDes(config, info, gpMaker, texMaker);
  eeTransDes(config, info, gpMaker, texMaker);
  eeRotDes(config, info, gpMaker, texMaker);

  // err
  dcmErr(config, info, gpMaker, texMaker);
  baseRotErr(config, info, gpMaker, texMaker);
  eeTransErr(config, info, gpMaker, texMaker);
  eeRotErr(config, info, gpMaker, texMaker);
  eeWrenchErr(config, info, gpMaker, texMaker);

  // ref
  mixedQuasiAccOptRef(config, info, gpMaker, texMaker);
  jointTorque(config, info, gpMaker, texMaker);
  rcMomRef(config, info, gpMaker, texMaker);
  eeWrenchRef(config, info, gpMaker, texMaker);
  extWrenchRef(config, info, gpMaker, texMaker);

  // index
  // localCop(config, info, gpMaker, texMaker);
  // netCop(config, info, gpMaker, texMaker);
  // stabilityIndex(config, info, gpMaker, texMaker);
  localCop4walking(config, info, gpMaker, texMaker);
  // netCop4walking(config, info, gpMaker, texMaker);
  // cmp4walking(config, info, gpMaker, texMaker);
  stabilityIndex4walking(config, info, gpMaker, texMaker);
  footPrint(config, info, gpMaker, texMaker);

  // main
  gpMaker.makeMainGp();
  texMaker.makeMainTex();
}
