#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeGpTimeLimb(Config &config, Info &info, string category, string name, string yLabel, string unit, int terminal)
{
  if(config.flag.debug) DEBUG;

  string xLabel = "Time [s]";

  int cur=0, sum;
  string temp;
  for(int l=1; l<info.value.node; l++){
    string setting =
      "reset\n"
      "load 'library/config.gp'\n"
      "load 'library/macro.gp'\n"
      "load 'library/set.gp'\n";

    string label =
      "set xlabel '"+xLabel+"'\n"
      "set ylabel 'Limb"+to_string(l)+" "+yLabel+"'";

  // smiyahara: categoryが小文字だから
    string MACRO;
    if(category=="controller")
      MACRO = "CONTROLLER";
    if(category=="model")
      MACRO = "MODEL";

    string out =
      "set output "+MACRO+"_EPS.'"+name+"Limb"+to_string(l)+".eps'\n";

    string plot = "plot ";

    sum=0;
    for(int i=2, node=1; i<info.limb[l].dof+2; i++, node++){
      plot +=
	MACRO+"_DAT.'"+name+".dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($"+to_string(cur+i)+"*"+unit+") t '"+to_string(node)+"' w l ls "+to_string(i-1);

      if(i<info.limb[l].dof+1)
	plot += ",\\\n";

      sum++;
    }
    cur += sum;

    string replot =
      "set terminal TERMINAL "+to_string(terminal+l)+"\n"
      "if(VIEWMODE) replot\n";

    temp +=
      setting + "\n" + label + "\n" + out + "\n" + plot + "\n\n" + replot +"\n\n";
  }

  string pathGp = config.link + "data/gp/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/" + category + "/";
  string pathGp_temp;

  pathGp_temp = pathGp+name+".gp";

  ofstream gp(pathGp_temp.c_str());
  if(!gp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    gp << temp;
    gp.close();
  }
}
