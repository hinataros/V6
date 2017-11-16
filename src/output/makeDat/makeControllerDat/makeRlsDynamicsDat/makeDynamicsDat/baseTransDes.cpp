#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::baseTransDes(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // desired base position
  name = "000_basePosDes";
  ofstream basePosDes((dir+name+".dat").c_str());
  if(!basePosDes)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      basePosDes << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].rBDes.transpose() << endl;
    basePosDes.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base pos. [mm]","K",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // desired base velocity
  name = "002_baseVelDes";
  ofstream baseVelDes((dir+name+".dat").c_str());
  if(!baseVelDes)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseVelDes << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].vBDes.transpose() << endl;
    baseVelDes.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base vel. [m/s]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // desired base acceleration
  name = "004_baseAccDes";
  ofstream baseAccDes((dir+name+".dat").c_str());
  if(!baseAccDes)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseAccDes << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].dvBDes.transpose() << endl;
    baseAccDes.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base acc. [m/s^2]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
