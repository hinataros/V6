/**
   @author Sho Miyahara 2018
   @modified by Akinori Miyata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::stabilityIndex4walkingDes(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  int stepNum = extractor.footPrintList.size();

  // VectorXd Max, Min;
  // Min = extractor.footPrintList[0].segment(0,2);
  // Max = extractor.footPrintList[stepNum-1].segment(0,2);

  texMaker.reset();

  reset();
  setFileName("stabilityIndexDes");

  setDatNum(4);
  // setDatName(1, "gCoMDes");
  // setDatName(2, "rndecmpDes");
  // setDatName(2, "rp");
  // setDatName(3, "xCoMDes");
  setDatName(1, "eCMPDes");
  setDatName(2, "eCMPDes");
  setDatName(3, "eCMPDes");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setXLabel("x [m]");
  gpMaker.setYLabel("y [m]");
  // gpMaker.setUnit("m");
  gpMaker.redef("XLABEL_OFFSET_Y = -0.8"); // IROS
  // gpMaker.redef("YLABEL_OFFSET_X = -0.25"); // IROS
  // gpMaker.add("set xtics 0.2"); // long
  // gpMaker.add("set ytics 0.1");
  // gpMaker.add("set size ratio "+to_string(2./9.));
  // gpMaker.add("set xrange[-0.1:0.8]");
  // gpMaker.add("set yrange[-0.1:0.1]");
  gpMaker.add("set xtics 0.2"); // 4step
  gpMaker.add("set ytics 0.1");
  gpMaker.add("set size ratio "+to_string(0.2/0.5)); // IROS
  gpMaker.add("set xrange[-0.1:0.4]");
  gpMaker.add("set yrange[-0.1:0.1]");

  double foot_size_x[2] = {-0.040, 0.058};
  double foot_size_y[2] = {0.0315, -0.0315};

  // draw foot print
  for(int i=0; i<stepNum; i++){
    if(nanCheck(extractor.footPrintList[i]))
      gpMaker.add("set object "+to_string(i+1)+" rect from "+to_string(extractor.footPrintList[i](0)+foot_size_x[0])+", "+to_string(extractor.footPrintList[i](1)+foot_size_y[0])+" to "+to_string(extractor.footPrintList[i](0)+foot_size_x[1])+", "+to_string(extractor.footPrintList[i](1)+foot_size_y[1])+" fs empty border rgb 'black'");
  }

  gpMaker.setDimention(4);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("stabilityIndex");
  texMaker.setCaption("Desired gCoM and xCoM and eCMP (and net CoP) values.");
  texMaker.makeTex();
}
