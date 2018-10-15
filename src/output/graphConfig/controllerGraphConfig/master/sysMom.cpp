/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::sysMom(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  texMaker.reset();

  reset();
  setFileName("pCRB");
  setVerticalDat("time");
  setHorizontalDat("pCRB");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CRB mom. [Ns]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("lCRB");
  setVerticalDat("time");
  setHorizontalDat("lCRB");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("CRB ang. mom. [Nms]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("pCth");
  setVerticalDat("time");
  setHorizontalDat("pCth");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Coupl. mom. [Ns]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("lCth");
  setVerticalDat("time");
  setHorizontalDat("lCth");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Coupl. ang. mom. [Nms]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("psys");
  setVerticalDat("time");
  setHorizontalDat("psys");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setYLabel("Sys. mom. [Ns]");
  gpMaker.setDimention(3);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  reset();
  setFileName("lCsys");
  setVerticalDat("time");
  setHorizontalDat("lCsys");
  makeDat();

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
