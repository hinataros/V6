/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeGp(Config &config, string category, string name, int limb, string yCommonLabel, string unit, int dimention, int terminal){
  if(limb <= array_length(limbName) && limbName[0] != "default")
    makeGp(config, category, name, limbName[limb-1] + " " + yCommonLabel, unit, dimention, terminal);
  else
    makeGp(config, category, name, "Limb"+to_string(limb) + " " + yCommonLabel, unit, dimention, terminal);
}

void RLS::Output::makeGp(Config &config, string category, string name, int limb, string xCommonLabel, string yCommonLabel, string unit, int dimention, int terminal){
  if(limb <= array_length(limbName) && limbName[0] != "default")
    makeGp(config, category, name, limbName[limb-1] + " " + xCommonLabel, limbName[limb-1] + " " + yCommonLabel, unit, dimention, "", terminal);
  else
    makeGp(config, category, name, "Limb"+to_string(limb) + " " + xCommonLabel, "Limb"+to_string(limb) + " " + yCommonLabel, unit, dimention, "", terminal);
}

void RLS::Output::makeGp(Config &config, string category, string name, string yLabel, string unit, int dimention, int terminal){
  makeGp(config, category, name, timeLabelStr, yLabel, unit, dimention, "", terminal);
}

void RLS::Output::makeGp(Config &config, string category, string name, string yLabel, string unit, int dimention, string add, int terminal){
  makeGp(config, category, name, timeLabelStr, yLabel, unit, dimention, add, terminal);
}

void RLS::Output::makeGp(Config &config, string category, string name, string xLabel, string yLabel, string unit, int dimention, int terminal){
  makeGp(config, category, name, xLabel, yLabel, unit, dimention, "", terminal);
}

void RLS::Output::makeGp(Config &config, string category, string name, string xLabel, string yLabel, string unit, int dimention, string add, int terminal)
{
  if(config.flag.debug) DEBUG;

  string setting =
    "reset\n"
    "load '"+config.dir.gp.ind+"library/macro.gp'\n\n"
    "load LIBRARY.'config.gp'\n"
    "load LIBRARY.'set.gp'\n";

  string label =
    "set xlabel '"+xLabel+"'\n"
    "set ylabel '"+yLabel+"'\n";

  // smiyahara: categoryが小文字だから
  string MACRO;
  if(category=="controller")
    MACRO = "CONTROLLER";
  if(category=="model")
    MACRO = "MODEL";

  string out =
    "set output "+MACRO+"_EPS.'"+name+".eps'\n";

  string plot = "plot ";
  if(xLabel == timeLabelStr)
    for(int i=2; i<dimention+2; i++){
      plot +=
        MACRO+"_DAT.'"+name+".dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($"+to_string(i)+"*"+unit+") t '' w l ls "+to_string(i-1);

      if(i<dimention+1)
        plot += ",\\\n";
    }

  else
    for(int i=1, j=1; j<dimention+1; i+=2, j++){
      plot +=
        MACRO+"_DAT.'"+name+".dat' every ::(T_OFFSET*SAMPLING) u ($"+to_string(i)+"*"+unit+"):($"+to_string(i+1)+"*"+unit+") t '' w l ls "+to_string(j);

      if(j<dimention)
        plot += ",\\\n";
    }

  string replot =
    "set terminal TERMINAL "+to_string(terminal)+"\n"
    "if(VIEWMODE) replot\n";

  ofstream gp((config.dir.gp.ind+category+"/"+name+".gp").c_str());
  if(!gp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    gp <<
      setting << endl <<
      label << endl <<
      out << endl <<
      add << endl <<
      plot << endl << endl <<
      replot << endl;
    gp.close();
  }
}
