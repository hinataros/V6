#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::comErr(Config &config, Info &info, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // com position error
  name = "034_comPosErr";
  ofstream comPosErr((path+name+".dat").c_str());
  if(!comPosErr)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      comPosErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].erC.transpose() << endl;
    comPosErr.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "CoM pos. err. [mm]","K",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // com velocity error
  name = "034_comVelErr";
  ofstream comVelErr((path+name+".dat").c_str());
  if(!comVelErr)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      comVelErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].evC.transpose() << endl;
    comVelErr.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "CoM vel. err. [m/s]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
