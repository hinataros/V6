/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::sysMom(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("pCRB");
  makeDat("t-pCRB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CRB mom. [Ns]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("lCRB");
  makeDat("t-lCRB");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CRB ang. mom. [Nms]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("pCth");
  makeDat("t-pCth");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Coupl. mom. [Ns]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("lCth");
  makeDat("t-lCth");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Coupl. ang. mom. [Nms]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("psys");
  makeDat("t-psys");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Sys. mom. [Ns]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("lCsys");
  makeDat("t-lCsys");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Sys. ang. mom. [Nms]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("sysMom");
  texMaker.setCaption("System spatial momentum values.");
  texMaker.makeTex();
}
