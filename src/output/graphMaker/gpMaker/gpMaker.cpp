/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "gpMaker.hpp"

RLS::GpMaker::GpMaker()
{
  initialize();
}

RLS::GpMaker::~GpMaker()
{
  vector<bool>().swap(flag);
  vector<int>().swap(dimention);
  vector<string>().swap(redef_str);
  vector<string>().swap(add_str);
  vector<string>().swap(scale);
  vector<int>().swap(exponent);
}

void RLS::GpMaker::initialize()
{
  load = "";

  reset();
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
  terminal = 0;

  vector<bool>().swap(flag);
  flag.push_back(true);

  vector<int>().swap(dimention);
  dimention.push_back(1);

  vector<string>().swap(redef_str);
  redef_str.push_back("");
  vector<string>().swap(add_str);
  add_str.push_back("");

  vector<string>().swap(scale);
  scale.push_back("1e+0");
  vector<int>().swap(exponent);
  exponent.push_back(0);

  point = 0;
}

void RLS::GpMaker::setName(string arg)
{
  name = arg;
}

void RLS::GpMaker::setLimb(int arg)
{
  numLimb = arg;

  flag.resize(arg, true);
  dimention.resize(arg, 1);
  redef_str.resize(arg, "");
  add_str.resize(arg, "");
  scale.resize(arg, "1e+0");
  exponent.resize(arg, 0);
}

void RLS::GpMaker::setLimbNum(int arg0, bool arg1)
{
  flag[arg0-1] = arg1;
}

void RLS::GpMaker::setXLabel(string arg)
{
  xLabel = arg;
}

void RLS::GpMaker::setYLabel(string arg)
{
  yLabel = arg;
}

void RLS::GpMaker::setUnit(string arg)
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
  for(int i=1; i<numLimb+1; i++)
    setScale(i, arg);
}

void RLS::GpMaker::setScale(int arg0, int arg1)
{
  if(arg1>=0)
    scale[arg0-1] = "1e+"+to_string(arg1);
  else
    scale[arg0-1] = "1e"+to_string(arg1);

  exponent[arg0-1] = -arg1;
}

void RLS::GpMaker::redef(string arg)
{
  for(int i=1; i<numLimb+1; i++){
    redef(i, arg);
  }
}

void RLS::GpMaker::redef(int limb, string arg)
{
  if(redef_str[limb-1]=="")
    redef_str[limb-1] = arg + "\n";
  else
    redef_str[limb-1] += arg + "\n";
}

void RLS::GpMaker::add(string arg)
{
  for(int i=1; i<numLimb+1; i++){
    add(i, arg);
  }
}

void RLS::GpMaker::add(int limb, string arg)
{
  if(add_str[limb-1]=="")
    add_str[limb-1] = arg + "\n";
  else
    add_str[limb-1] += arg + "\n";
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
  for(int l=1; l<numLimb+1; l++){
    if(flag[l-1])
      code += makeCode(l);

    if(xLabel == timeLabelStr)
      point += dimention[l-1];
    else
      point += 2*dimention[l-1];        
  }

  ofstream gpMaker((path_gp_ind+"src/"+name+".gp").c_str());
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
    "load DIR_LIB.'config.gp'\n"
    "load DIR_LIB.'set.gp'\n";

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
      "set xlabel '"+xLabel+"' tc rgb XLABEL_COLOR\n"
      // "set ylabel '"+yLabel+"'\n";
      "set label 1 at graph YLABEL_OFFSET_X, YLABEL_OFFSET_Y center '"+yLabel+"' rotate by 90  tc rgb YLABEL_COLOR\n";
  else
    xylabel =
      "set xlabel '"+xtemp+"' tc rgb XLABEL_COLOR\n"
      // "set ylabel '"+ytemp+"'\n";
      "set label 1 at graph YLABEL_OFFSET_X, YLABEL_OFFSET_Y center '"+ytemp+"' rotate by 90  tc rgb YLABEL_COLOR\n";

  string label = "";
  if(exponent[limb-1])
    label += "set label 2 'x10^{"+to_string(exponent[limb-1])+"}' at screen DECIMAL_COORD_X, DECIMAL_COORD_Y\n";

  string out =
    "set output DIR_EPS.'"+name+suffix+".eps'\n";

  string plot = "plot \\\n";
  if(xLabel == timeLabelStr){
    for(int i=2; i<dimention[limb-1]+2; i++){
      plot +=
        "DIR_DAT.'"+name+".dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($"+to_string(point+i)+"*"+unit+"*"+scale[limb-1]+") t '' w l ls "+to_string(i-1);

      if(i<dimention[limb-1]+1)
        plot += ",\\\n";
    }
  }
  else{
    for(int i=1, j=1; j<dimention[limb-1]+1; i+=2, j++){
      plot +=
        "DIR_DAT.'"+name+".dat' every ::(T_OFFSET*SAMPLING) u ($"+to_string(point+i)+"*"+unit+"*"+scale[limb-1]+"):($"+to_string(point+i+1)+"*"+unit+"*"+scale[limb-1]+") t '' w l ls "+to_string(j);

      if(j<dimention[limb-1])
        plot += ",\\\n";
    }
  }

  string replot =
    "set terminal TERMINAL "+to_string(terminal)+"\n"
    "if(VIEWMODE) replot\n";

  string code =
    setting+"\n"+
    redef_str[limb-1]+"\n"+
    xylabel+"\n"+
    label+"\n"+
    out+"\n"+
    add_str[limb-1]+"\n"+
    plot+"\n\n"+
    replot+"\n";

  return code;
}

void RLS::GpMaker::addLoad()
{
  load += "load '" + path_gp_ind + "src/" + name+".gp'\n";
}

void RLS::GpMaker::setMainGpName()
{
  main_gp_name = "main.gp";
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
