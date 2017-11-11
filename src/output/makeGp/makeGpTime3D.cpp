#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeGpTime3D(Config &config, string category, string name, string yLabel, string unit, int terminal)
{
  if(config.flag.debug) DEBUG;

  string xLabel = "Time [s]";

  string setting =
    "reset\n"
    "load 'library/config.gp'\n"
    "load 'library/macro.gp'\n"
    "load 'library/set.gp'\n";

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
  for(int i=2; i<5; i++){
    plot +=
      MACRO+"_DAT.'"+name+".dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($"+to_string(i)+"*"+unit+") t '' w l ls "+to_string(i-1);

    if(i<4)
      plot += ",\\\n";
  }

  string replot =
    "set terminal TERMINAL "+to_string(terminal)+"\n"
    "if(VIEWMODE) replot\n";

  string pathGp = config.link + "data/gp/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/" + category + "/";

  string pathGp_temp = pathGp+name+".gp";

  ofstream gp(pathGp_temp.c_str());
  if(!gp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    gp <<
      setting << endl <<
      label << endl <<
      out << endl <<
      plot << endl << endl <<
      replot << endl;
    gp.close();
  }
}
