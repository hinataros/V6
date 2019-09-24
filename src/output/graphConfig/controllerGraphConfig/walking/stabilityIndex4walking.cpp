/**
   @author Sho Miyahara 2018
   @modified by Akinori Miyata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"


void RLS::Output::stabilityIndex4walking(GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  int stepNum = extractor.footPrintList.size();

  // VectorXd Max, Min;
  // Min = extractor.footPrintList[0].segment(0,2);
  // Max = extractor.footPrintList[stepNum-1].segment(0,2);

  texMaker.reset();

  reset();
  setFileName("stabilityIndex");

  setDatNum(4);
  setDatName(1, "gCoM");
  // setDatName(2, "rndecmpDes");
  setDatName(2, "rp");
  setDatName(3, "xCoM");
  setDatName(4, "eCMPRef");
  makeDat();

  // gpMaker.reset(); // amiyata makeGraphへ移行
  gpMaker.setName(file_name);
  gpMaker.setXLabel("x [m]");
  gpMaker.setYLabel("y [m]");
  // gpMaker.setUnit("m");

  // amiyata addでやろう
  // gpMaker.redef("XLABEL_OFFSET_Y = -0.8");
  // gpMaker.redef("YLABEL_OFFSET_X = -0.25");
  // gpMaker.add("set xtics 0.2"); // 4step
  // gpMaker.add("set ytics 0.1");
  // gpMaker.add("set size ratio "+to_string(0.8/0.45));
  // gpMaker.add("set xrange[-0.1:0.35]");
  // gpMaker.add("set yrange[-0.7:0.1]");

  // footPrint
  vector<Vector2d> *fp = new vector<Vector2d>[stepNum];
  Vector3d fp3d;
  for(int i=0; i<stepNum; i++){
    for(int j=0; j<(signed int)extractor.soleConvex[extractor.footPrintList[i].ee].size(); j++){
      fp3d << extractor.soleConvex[extractor.footPrintList[i].ee][j], 0.;
      fp[i].push_back((extractor.footPrintList[i].att*fp3d).head(2));
    }
    fp[i].push_back(fp[i][0]); // close BoS convex
  }

  int arrowNum = 1;
  for(int i=0; i<stepNum; i++){
    if(nanCheck(extractor.footPrintList[i].pos)){
      for(int j=0; j<(signed int)fp[i].size()-1; j++){
        ostringstream oss;
        oss << "set arrow " << arrowNum << " from "\
          << (extractor.footPrintList[i].pos(0)+fp[i][j](0)) <<", "\
          << (extractor.footPrintList[i].pos(1)+fp[i][j](1)) <<" "\
          << "to "
          << (extractor.footPrintList[i].pos(0)+fp[i][j+1](0)) <<", "\
          << (extractor.footPrintList[i].pos(1)+fp[i][j+1](1)) <<" "\
          << "nohead";

        gpMaker.add(oss.str());
        arrowNum ++;
      }
    }
  }

  gpMaker.setDimention(4);
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("stabilityIndex");
  texMaker.setCaption("gCoM and net CoP and xCoM and eCMP values.");
  texMaker.makeTex();
}
