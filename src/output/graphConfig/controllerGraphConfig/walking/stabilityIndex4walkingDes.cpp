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
  setDatName(1, "gCoMDes");
  setDatName(2, "rndecmpDes");
  // setDatName(2, "rp");
  // setDatName(3, "xCoMDes");
  setDatName(3, "eCMPDes");
  makeDat();

  // gpMaker.reset(); // amiyata
  gpMaker.setName(file_name);
  gpMaker.setXLabel("x [m]");
  gpMaker.setYLabel("y [m]");
  // gpMaker.setUnit("m");

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
  texMaker.setCaption("Desired gCoM and xCoM and eCMP (and net CoP) values.");
  texMaker.makeTex();
}
