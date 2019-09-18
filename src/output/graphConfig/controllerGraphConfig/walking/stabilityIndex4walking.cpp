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

  setDatNum(3);
  setDatName(1, "gCoM");
  // setDatName(2, "rndecmpDes");
  // setDatName(2, "rp");
  setDatName(2, "xCoM");
  setDatName(3, "eCMPRef");
  makeDat();

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setXLabel("x [m]");
  gpMaker.setYLabel("y [m]");
  // gpMaker.setUnit("m");
  gpMaker.redef("XLABEL_OFFSET_Y = -0.8");
  // gpMaker.redef("YLABEL_OFFSET_X = -0.25");
  gpMaker.add("set xtics 0.2"); // 4step
  gpMaker.add("set ytics 0.1");
  gpMaker.add("set size ratio "+to_string(0.8/0.45));
  gpMaker.add("set xrange[-0.1:0.35]");
  gpMaker.add("set yrange[-0.7:0.1]");

  // Vector3d foot_point;
  // foot_size_x <<
  //   -0.040,
  //   0.058,
  //   0.;
  // foot_size_y <<
  //   0.0315,
  //   -0.0315,
  //   0.;
  int footNum = 2;
  vector<Vector2d> *fp = new vector<Vector2d>[footNum];
  Vector3d fp3d;
  for(int i=0; i<(signed int)footNum; i++){
    for(int j=0; j<(signed int)extractor.soleConvex[i].size(); j++){
      fp3d << extractor.soleConvex[i][j], 0.;
      fp[i].push_back((extractor.footPrintList[i].att*fp3d).head(2));
    }
    fp[i].push_back(fp[i][0]); // close BoS convex
  }

  // for(int i=0; i<(signed int)footNum; i++)
  //   for(int j=0; j<(signed int)fp[i].size(); j++)
  //     o(fp[i][j]);
  // draw foot print
  // straight only
  // for(int i=0; i<stepNum; i++){
  //   if(nanCheck(extractor.footPrintList[i]))
  //     gpMaker.add("set object "+to_string(i+1)+" rect from "+to_string(extractor.footPrintList[i](0)+foot_size_x(0))+", "+to_string(extractor.footPrintList[i](1)+foot_size_y(0))+" to "+to_string(extractor.footPrintList[i](0)+foot_size_x(1))+", "+to_string(extractor.footPrintList[i](1)+foot_size_y(1))+" fs empty border rgb 'black'");
  // }
  for(int i=0; i<stepNum; i++){
    if(nanCheck(extractor.footPrintList[i].pos)){
      ostringstream oss;
      for(int j=0; j<(signed int)fp[extractor.footPrintList[i].ee].size()-1; j++){
        oss << "set arrow " << (i+1) << " from "\
          << (extractor.footPrintList[i].pos(0)+fp[extractor.footPrintList[i].ee][j](0)) <<", "\
          << (extractor.footPrintList[i].pos(1)+fp[extractor.footPrintList[i].ee][j](1)) <<", "\
          << "to "
          << (extractor.footPrintList[i].pos(0)+fp[extractor.footPrintList[i].ee][j+1](0)) <<", "\
          << (extractor.footPrintList[i].pos(1)+fp[extractor.footPrintList[i].ee][j+1](1)) <<", "\
          << " nohead rgb 'black'";
          // o(oss.str());

        // gpMaker.add(oss.str());
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
