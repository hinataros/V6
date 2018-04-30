/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "gpMaker.hpp"

RLS::GpMaker::GpMaker()
{
  load = "";
  category = "";

  reset();
}

RLS::GpMaker::GpMaker(string arg)
{
  load = "";
  category = "";

  reset();
  setCategory(arg);
}

RLS::GpMaker::~GpMaker()
{
  vector<int>().swap(dimention);
  vector<string>().swap(addStr);
}

void RLS::GpMaker::reset()
{
  name = "default";
  suffix = "";
  numLimb = 1;
  limbLabel = "";
  xLabel = timeLabelStr;
  yLabel = "default";
  unit = "E";
  scale = "1e+0";
  exponent = 0;
  terminal = 0;

  vector<int>().swap(dimention);
  dimention.push_back(1);

  vector<string>().swap(addStr);
  addStr.push_back("");

  point = 0;
}

void RLS::GpMaker::setCategory(string arg)
{
  category = arg;
  transform(arg.begin(), arg.end(), arg.begin(), ::toupper);
  CATEGORY = arg;
}

void RLS::GpMaker::setName(string arg)
{
  name = arg;
}

void RLS::GpMaker::setLimb(int arg)
{
  numLimb = arg;

  dimention.resize(arg, 1);
  addStr.resize(arg, "");
}

void RLS::GpMaker::setXLabel(string arg)
{
  xLabel = arg;
}

void RLS::GpMaker::setYLabel(string arg)
{
  yLabel = arg;
}

void RLS::GpMaker::chUnit(string arg)
{
  transform(arg.begin(), arg.end(), arg.begin(), ::toupper);
  unit = arg;
}

void RLS::GpMaker::setDimention(int arg)
{
  for(int i=1; i<numLimb+1; i++)
    setDimention(i, arg);
}

void RLS::GpMaker::setDimention(int arg0, int arg1)
{
  dimention[arg0-1] = arg1;
}

void RLS::GpMaker::setScale(int arg)
{
  if(arg>=0)
    scale = "1e+"+to_string(arg);
  else
    scale = "1e"+to_string(arg);

  exponent = -arg;
}

void RLS::GpMaker::add(string arg)
{
  for(int i=1; i<numLimb+1; i++){
    add(i, arg);
  }
}

void RLS::GpMaker::add(int limb, string arg)
{
  if(addStr[limb-1]=="")
    addStr[limb-1] = arg + "\n";
  else
    addStr[limb-1] += arg + "\n";
}

void RLS::GpMaker::setTerminal(int arg)
{
  terminal = arg;
}

void RLS::GpMaker::setSuffix(int arg)
{
  if(numLimb==1)
    suffix = "";
  else
    suffix = "Limb"+to_string(arg);
}

void RLS::GpMaker::setLimbLabel(int arg)
{
  if(numLimb <= static_cast<int>(array_length(limbName)) && limbName[0] != "default")
    limbLabel = limbName[arg-1];
  else
    limbLabel = "Limb"+to_string(arg);
}

void RLS::GpMaker::makeGp()
{
  string code;
  for(int l=1; l<numLimb+1; l++)
    code += makeCode(l);

  ofstream gpMaker((path_gp_ind+category+"/"+name+".gp").c_str());
  if(!gpMaker)
    cout << path_gp_ind << ": " << endl << "file open error..." << endl;
  else{
    gpMaker << code;
    gpMaker.close();
  }

  addLoad();
}

string RLS::GpMaker::makeCode(int limb)
{
  setSuffix(limb);
  setLimbLabel(limb);

  string setting =
    "reset\n"
    "load '"+path_gp_ind+"library/macro.gp'\n\n"
    "load LIBRARY.'config.gp'\n"
    "load LIBRARY.'set.gp'\n";

  // smiyahara: とりあえず ***********************
  string xtemp;
  if(xLabel!=timeLabelStr)
    xtemp = limbLabel + " " + xLabel;
  else
    xtemp = xLabel;

  string ytemp = limbLabel + " " + yLabel;

  string legEE[2] = {"leg EE", "foot"};
  string armEE[2] = {"arm EE", "hand"};

  int s = (int)xtemp.find(legEE[0]);
  if(s>0)
    xtemp.replace(s, legEE[0].size(), legEE[1]);
  s = (int)xtemp.find(armEE[0]);
  if(s>0)
    xtemp.replace(s, armEE[0].size(), armEE[1]);

  s = (int)ytemp.find(legEE[0]);
  if(s>0)
    ytemp.replace(s, legEE[0].size(), legEE[1]);
  s = (int)ytemp.find(armEE[0]);
  if(s>0)
    ytemp.replace(s, armEE[0].size(), armEE[1]);
  // **********************************************
  string xylabel;
  if(numLimb==1)
    xylabel =
      "set xlabel '"+xLabel+"'\n"
      // "set ylabel '"+yLabel+"'\n";
      "set label 1 at graph YLABEL_OFFSET_X, YLABEL_OFFSET_Y center '"+yLabel+"' rotate by 90\n";
  else
    xylabel =
      "set xlabel '"+xtemp+"'\n"
      // "set ylabel '"+ytemp+"'\n";
      "set label 1 at graph YLABEL_OFFSET_X, YLABEL_OFFSET_Y center '"+ytemp+"' rotate by 90\n";

  string label = "";
  if(exponent)
    label += "set label 2 'x10^{"+to_string(exponent)+"}' at screen DECIMAL_COORD_X, DECIMAL_COORD_Y\n";

  string out =
    "set output "+CATEGORY+"_EPS.'"+name+suffix+".eps'\n";

  string plot = "plot \\\n";
  if(xLabel == timeLabelStr){
    for(int i=2; i<dimention[limb-1]+2; i++){
      plot +=
        CATEGORY+"_DAT.'"+name+".dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($"+to_string(point+i)+"*"+unit+"*"+scale+") t '' w l ls "+to_string(i-1);

      if(i<dimention[limb-1]+1)
        plot += ",\\\n";
    }point += dimention[limb-1];
  }
  else{
    for(int i=1, j=1; j<dimention[limb-1]+1; i+=2, j++){
      plot +=
        CATEGORY+"_DAT.'"+name+".dat' every ::(T_OFFSET*SAMPLING) u ($"+to_string(point+i)+"*"+unit+"*"+scale+"):($"+to_string(point+i+1)+"*"+unit+"*"+scale+") t '' w l ls "+to_string(j);

      if(j<dimention[limb-1])
        plot += ",\\\n";
    }point += 2*dimention[limb-1];
  }

  string replot =
    "set terminal TERMINAL "+to_string(terminal)+"\n"
    "if(VIEWMODE) replot\n";

  string code =
    setting+"\n"+
    addStr[limb-1]+"\n"+
    xylabel+"\n"+
    label+"\n"+
    out+"\n"+
    plot+"\n\n"+
    replot+"\n";

  return code;
}

void RLS::GpMaker::addLoad()
{
  load += "load '" + path_gp_ind + category + "/" + name+".gp'\n";
}

void RLS::GpMaker::setMainGpName(string arg)
{
  main_gp_name = arg + ".gp";
}

void RLS::GpMaker::makeMainGp()
{
  ofstream main((path_gp_ind+main_gp_name).c_str());
  if(!main)
    cout << path_gp_ind+main_gp_name << ": " << endl << "file open error..." << endl;
  else{
    main << load << endl;
    main.close();
  }
}