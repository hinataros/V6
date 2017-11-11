#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::com(Config &config, Info &info, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // CoM position
  name = "030_comPos";
  ofstream comPos((path+name+".dat").c_str());
  if(!comPos)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      comPos << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].rC.transpose() << endl;
    comPos.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "CoM pos. [mm]","K",0);
    load += "load 'model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "model", "1.0", name);
  }

  // com velocity
  name = "031_comVel";
  ofstream comVel((path+name+".dat").c_str());
  if(!comVel)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      comVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].vC.transpose() << endl;
    comVel.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "CoM vel. [m/s]","E",2);
    load += "load 'model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "model", "1.0", name);
  }

  return minipage;
}
