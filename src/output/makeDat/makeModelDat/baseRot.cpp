#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::baseRot(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // base orientation
  name = "001_baseOrient";
  ofstream baseOrient((dir+name+".dat").c_str());
  if(!baseOrient)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseOrient << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].xiB.transpose() << endl;
    baseOrient.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "Base orient. [deg]","RAD2DEG",1);
    load += "load 'model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "model", "1.0", name);
  }

  // base angular velocity
  name = "003_baseAngVel";
  ofstream baseAngVel((dir+name+".dat").c_str());
  if(!baseAngVel)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseAngVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].wB.transpose() << endl;
    baseAngVel.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "Base ang. vel. [rad/s]","E",3);
    load += "load 'model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "model", "1.0", name);
  }

  return minipage;
}
