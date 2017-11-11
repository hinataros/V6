#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::baseTransErr(Config &config, Info &info, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // base position error
  name = "030_basePosErr";
  ofstream basePosErr((path+name+".dat").c_str());
  if(!basePosErr)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      basePosErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].erB.transpose() << endl;
    basePosErr.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Base pos. err. [mm]","K",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // base velocity error
  name = "032_baseVelErr";
  ofstream baseVelErr((path+name+".dat").c_str());
  if(!baseVelErr)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseVelErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].evB.transpose() << endl;
    baseVelErr.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Base vel. err. [m/s]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
